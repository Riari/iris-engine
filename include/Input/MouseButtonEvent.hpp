#pragma once

#include <memory>
#include <utility>

#include "InputBinding.hpp"
#include "InputEventHandler.hpp"

namespace OGL
{
    class MouseButtonEvent : public InputEventHandler
    {
    public:
        MouseButtonEvent(const Window &window, int button, int action, std::shared_ptr<InputBinding> binding = nullptr) :
                InputEventHandler(window),
                m_button(button),
                m_action(action),
                m_binding(std::move(binding)) {}

        [[nodiscard]] int GetButton() const { return m_button; }
        [[nodiscard]] int GetAction() const { return m_action; }
        std::shared_ptr<InputBinding> GetBinding() { return m_binding; }

    private:
        int m_button;
        int m_action;
        std::shared_ptr<InputBinding> m_binding;
    };
}