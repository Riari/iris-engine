#include <algorithm>

#include <fmt/core.h>
#include <GLFW/glfw3.h>

#include "Exception/KeyInUseException.h"
#include "InputBinding.h"
#include "InputManager.h"

namespace OGL::Input
{
    InputManager::InputManager()
    {
        Setup();
    }

    void InputManager::Setup()
    {
        MoveForward = new InputBinding("Move Forward", GLFW_KEY_W);
        MoveBackward = new InputBinding("Move Backward", GLFW_KEY_S);
        StrafeLeft = new InputBinding("Strafe Left", GLFW_KEY_A);
        StrafeRight = new InputBinding("Strafe Right", GLFW_KEY_D);
        GoUp = new InputBinding("Go Up", GLFW_KEY_SPACE);
        GoDown = new InputBinding("Go Down", GLFW_KEY_C);

        m_bindings = {
                MoveForward,
                MoveBackward,
                StrafeLeft,
                StrafeRight,
                GoUp,
                GoDown
        };
    }

    void InputManager::OnKeyCallback(int key, int scancode, int action, int mods)
    {
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
    }

    void InputManager::OnKeybindChange(InputBinding *targetBinding, int key, bool isPrimary)
    {
        for (auto binding : m_bindings)
        {
            auto keys = binding->GetKeys();
            if (std::find(keys.begin(), keys.end(), key) != keys.end())
            {
                throw Exception::KeyInUseException(fmt::format("Key {0} is already bound to {1}.", key, binding->GetLabel()));
            }
        }

        if (isPrimary) targetBinding->BindPrimary(key);
        else targetBinding->BindSecondary(key);
    }

    bool InputManager::IsPressed(InputBinding *binding)
    {
        auto boundKeys = binding->GetKeys();

        for (auto key : m_keysPressed)
        {
            for (auto boundKey : boundKeys)
            {
                if (boundKey == key) return true;
            }
        }

        return false;
    }

    bool InputManager::IsHeld(InputBinding *binding)
    {
        auto boundKeys = binding->GetKeys();

        for (auto key : m_keysHeld)
        {
            for (auto boundKey : boundKeys)
            {
                if (boundKey == key) return true;
            }
        }

        return false;
    }

    bool InputManager::IsReleased(InputBinding *binding)
    {
        auto boundKeys = binding->GetKeys();

        for (auto key : m_keysReleased)
        {
            for (auto boundKey : boundKeys)
            {
                if (boundKey == key) return true;
            }
        }

        return false;
    }

    bool InputManager::IsCtrlHeld() const
    {
        return m_isCtrlHeld;
    }

    bool InputManager::IsAltHeld() const
    {
        return m_isAltHeld;
    }

    bool InputManager::IsShiftHeld() const
    {
        return m_isShiftHeld;
    }
}
