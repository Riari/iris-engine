#pragma once

#include <memory>
#include <utility>

#include "InputBinding.hpp"
#include "InputEventHandler.hpp"

namespace OGL
{
    class KeyEvent : public InputEventHandler
    {
    public:
        KeyEvent(const Window &window, int key, int action, bool isCtrlHeld, bool isShiftHeld, bool isAltHeld, std::shared_ptr<InputBinding> binding = nullptr)
            : InputEventHandler(window), m_key(key), m_action(action), m_binding(std::move(binding)) {}

        [[nodiscard]] int GetKey() const { return m_key; }
        [[nodiscard]] int GetAction() const { return m_action; }
        std::shared_ptr<InputBinding> GetBinding() { return m_binding; }

    private:
        int m_key;
        int m_action;
        bool m_isCtrlHeld = false;
        bool m_isShiftHeld = false;
        bool m_isAltHeld = false;
        std::shared_ptr<InputBinding> m_binding;
    };
}