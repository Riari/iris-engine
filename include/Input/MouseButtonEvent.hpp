#pragma once

#include <memory>
#include <utility>

#include "InputBinding.hpp"

namespace OGL
{
    class MouseButtonEvent
    {
    public:
        MouseButtonEvent(int button, int action, std::shared_ptr<InputBinding> binding = nullptr) :
            m_button(button),
            m_action(action),
            m_binding(binding) {}

        [[nodiscard]] int GetButton() const { return m_button; }
        [[nodiscard]] int GetAction() const { return m_action; }
        std::shared_ptr<InputBinding> GetBinding() { return m_binding; }

    private:
        int m_button;
        int m_action;
        std::shared_ptr<InputBinding> m_binding;
    };
}