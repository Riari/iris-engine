#include <algorithm>
#include <utility>

#include <fmt/core.h>
#include <GLFW/glfw3.h>

#include "Exception/KeyInUseException.h"
#include "Action.h"
#include "InputBinding.h"
#include "InputManager.h"
#include "Exception/PrimaryKeyMissingException.h"

namespace OGL::Input
{
    void InputManager::RegisterBinding(std::string name, int primaryKey, int secondaryKey, bool force)
    {
        if (primaryKey == GLFW_KEY_UNKNOWN) throw Exception::PrimaryKeyMissingException();

        if (!force)
        {
            ValidateKeyAvailable(primaryKey);
            ValidateKeyAvailable(secondaryKey);
        }

        auto pBinding = std::make_shared<InputBinding>(std::move(name), primaryKey, secondaryKey);
        m_bindings[primaryKey] = pBinding;

        if (secondaryKey != GLFW_KEY_UNKNOWN)
        {
            m_bindings[secondaryKey] = pBinding;
        }
    }

    void InputManager::OnKeyCallback(int key, int scancode, int action, int mods)
    {
        auto handlers = GetHandlers<KeyPress>();
        if (handlers.empty()) return;

        m_keysPressed.clear();
        m_keysReleased.clear();

        m_isCtrlHeld = (mods & GLFW_MOD_CONTROL) != 0;
        m_isAltHeld = (mods & GLFW_MOD_ALT) != 0;
        m_isShiftHeld = (mods & GLFW_MOD_SHIFT) != 0;

        if (action == GLFW_PRESS)
        {
            m_keysPressed.push_back(key);
            m_keysHeld.push_back(key);
        }
        else if (action == GLFW_RELEASE)
        {
            m_keysPressed.erase(std::remove(m_keysPressed.begin(), m_keysPressed.end(), key), m_keysPressed.end());
            m_keysHeld.erase(std::remove(m_keysHeld.begin(), m_keysHeld.end(), key), m_keysHeld.end());
            m_keysReleased.push_back(key);
        }

        std::vector<int> seen;

        for (auto k : m_keysHeld)
        {
            auto binding = m_bindings[k];

            for (const auto& handler : handlers)
            {
                handler(KeyPress(k, Action::Hold, binding));
            }

            seen.push_back(k);
        }

        for (auto k : m_keysPressed)
        {
            if (std::find(seen.begin(), seen.end(), k) != seen.end()) continue;

            auto binding = m_bindings[k];

            for (const auto& handler : handlers)
            {
                handler(KeyPress(k, Action::Press, binding));
            }
        }

        for (auto k : m_keysReleased)
        {
            auto binding = m_bindings[k];

            for (const auto& handler : handlers)
            {
                handler(KeyPress(k, Action::Release, binding));
            }
        }
    }

    bool InputManager::IsCtrlHeld()
    {
        return m_isCtrlHeld;
    }

    bool InputManager::IsAltHeld()
    {
        return m_isAltHeld;
    }

    bool InputManager::IsShiftHeld()
    {
        return m_isShiftHeld;
    }

    void InputManager::ValidateKeyAvailable(int key)
    {
        if (m_bindings.count(key) == 1)
        {
            throw Exception::KeyInUseException(fmt::format("Key {0} is already bound to {1}.", key, m_bindings[key]->GetName()));
        }
    }
}
