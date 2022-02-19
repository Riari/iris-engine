#pragma once

#include "WindowManager.hpp"

namespace Iris
{
    template<typename T>
    class WindowEventHandler
    {
    public:
        WindowEventHandler()
        {
            WindowManager::RegisterHandler<T>([this](const T& event) { Handle(event); });
        }

        virtual void Handle(T) = 0;
    };
}