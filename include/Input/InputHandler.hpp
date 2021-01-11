#pragma once

#include "InputManager.hpp"

namespace OGL
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