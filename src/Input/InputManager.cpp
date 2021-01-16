#include <algorithm>
#include <utility>

#include <fmt/core.h>
#include <GLFW/glfw3.h>

#include "Input/Exception/KeyInUseException.hpp"
#include "Input/Exception/PrimaryKeyMissingException.hpp"
#include "Input/InputBinding.hpp"
#include "Input/InputManager.hpp"

using namespace OGL;

void InputManager::RegisterBinding(int id, int primaryKey, int secondaryKey, bool force)
{
    if (primaryKey == GLFW_KEY_UNKNOWN) throw PrimaryKeyMissingException();

    if (!force)
    {
        ValidateKeyAvailable(primaryKey);
        ValidateKeyAvailable(secondaryKey);
    }

    auto pBinding = std::make_shared<InputBinding>(id, primaryKey, secondaryKey);
    m_bindings[primaryKey] = pBinding;

    if (secondaryKey != GLFW_KEY_UNKNOWN)
    {
        m_bindings[secondaryKey] = pBinding;
    }
}

void InputManager::OnMouseButtonCallback(const Window &window, int button, int action, int mods)
{
    UpdateModifierKeys(mods);
    DispatchMouseButtonEvent(window, button, action);
}

void InputManager::OnCursorPosCallback(const Window &window, double x, double y)
{
    DispatchMouseMoveEvent(window, x, y);
}

void InputManager::OnScrollCallback(const Window &window, double x, double y)
{
    DispatchMouseScrollEvent(window, x, y);
}

void InputManager::OnKeyCallback(const Window &window, int key, int scancode, int action, int mods)
{
    UpdateModifierKeys(mods);

    m_keysReleased.clear();

    if (action == GLFW_PRESS)
    {
        m_keysPressed.push_back(key);
    }
    else if (action == GLFW_RELEASE)
    {
        m_keysPressed.erase(std::remove(m_keysPressed.begin(), m_keysPressed.end(), key), m_keysPressed.end());
        m_keysReleased.push_back(key);
    }

    for (auto k : m_keysPressed) DispatchKeyEvent(window, k, GLFW_PRESS);
    for (auto k : m_keysReleased) DispatchKeyEvent(window, k, GLFW_RELEASE);
}

bool InputManager::IsCtrlDown()
{
    return m_isCtrlDown;
}

bool InputManager::IsShiftDown()
{
    return m_isAltHeld;
}

bool InputManager::IsAltDown()
{
    return m_isShiftDown;
}

bool InputManager::IsSuperDown()
{
    return m_isSuperDown;
}

bool InputManager::IsCapsLockOn()
{
    return m_isCapsLockOn;
}

bool InputManager::IsNumLockOn()
{
    return m_isNumLockOn;
}

void InputManager::ValidateKeyAvailable(int key)
{
    if (m_bindings.count(key) == 1)
    {
        throw KeyInUseException(fmt::format("Key {0} is already bound to ID {1}.", key, m_bindings[key]->GetID()));
    }
}

void InputManager::UpdateModifierKeys(int mods)
{
    m_isCtrlDown = (mods & GLFW_MOD_CONTROL) != 0;
    m_isAltHeld = (mods & GLFW_MOD_ALT) != 0;
    m_isShiftDown = (mods & GLFW_MOD_SHIFT) != 0;
    m_isSuperDown = (mods & GLFW_MOD_SUPER) != 0;
    m_isCapsLockOn = (mods & GLFW_MOD_CAPS_LOCK) != 0;
    m_isNumLockOn = (mods & GLFW_MOD_NUM_LOCK) != 0;
}

void InputManager::DispatchMouseButtonEvent(const Window &window, int button, int action)
{
    auto handlers = GetHandlers<MouseButtonEvent>();
    if (handlers.empty()) return;

    for (const auto& handler : handlers)
    {
        handler(MouseButtonEvent(window, button, action));
    }
}

void InputManager::DispatchMouseMoveEvent(const Window &window, double x, double y)
{
    auto handlers = GetHandlers<MouseMoveEvent>();
    if (handlers.empty()) return;

    for (const auto& handler : handlers)
    {
        handler(MouseMoveEvent(window, x, y));
    }
}

void InputManager::DispatchMouseScrollEvent(const Window &window, double x, double y)
{
    auto handlers = GetHandlers<MouseScrollEvent>();
    if (handlers.empty()) return;

    for (const auto& handler : handlers)
    {
        handler(MouseScrollEvent(window, x, y));
    }
}

void InputManager::DispatchKeyEvent(const Window &window, int key, int action)
{
    auto handlers = GetHandlers<KeyEvent>();
    if (handlers.empty()) return;

    auto binding = m_bindings[key];

    for (const auto& handler : handlers)
    {
        handler(KeyEvent(window, key, action, m_isCtrlDown, m_isAltHeld, m_isShiftDown, binding));
    }
}
