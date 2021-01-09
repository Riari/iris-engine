#pragma once

#include <memory>
#include <utility>

#include "Action.h"
#include "InputBinding.h"

namespace OGL::Input
{
    class MouseButtonPress
    {
    public:
        MouseButtonPress(int button, Action action, std::shared_ptr<InputBinding> binding = nullptr) :
            m_button(button),
            m_action(action),
            m_binding(binding) {}

        [[nodiscard]] int GetButton() const { return m_button; }
        [[nodiscard]] Action GetAction() const { return m_action; }
        std::shared_ptr<InputBinding> GetBinding() { return m_binding; }

    private:
        int m_button;
        Action m_action;
        std::shared_ptr<InputBinding> m_binding;
    };
}