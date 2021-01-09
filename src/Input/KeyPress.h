#pragma once

#include <memory>
#include <utility>

#include "Action.h"
#include "InputBinding.h"

namespace OGL::Input
{
    class KeyPress
    {
    public:
        KeyPress(int key, Action action, std::shared_ptr<InputBinding> binding = nullptr) : m_key(key), m_action(action), m_binding(binding) {}

        [[nodiscard]] int GetKey() const { return m_key; }
        [[nodiscard]] Action GetAction() const { return m_action; }
        std::shared_ptr<InputBinding> GetBinding() { return m_binding; }

    private:
        int m_key;
        Action m_action;
        std::shared_ptr<InputBinding> m_binding;
    };
}