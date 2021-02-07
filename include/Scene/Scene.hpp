#pragma once

#include "Window/Window.hpp"

namespace Iris
{
    class Scene
    {
    public:
        virtual void Setup(float aspectRatio) = 0;
        virtual void Update(Window&) = 0;
        virtual void Render(Window&) = 0;
        virtual void Teardown() = 0;
    };
}