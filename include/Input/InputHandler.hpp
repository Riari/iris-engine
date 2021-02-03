#pragma once

#include "InputManager.hpp"

namespace Iris
{
    template<typename T>
    class InputHandler
    {
    public:
        InputHandler()
        {
            InputManager::RegisterHandler<T>([this](const T& event) { Handle(event); });
        }

        virtual void Handle(T) = 0;
    };
}