#pragma once

namespace OGL::Window
{
    class ScrollHandler
    {
    public:
        virtual void OnScrollCallback(double x, double y) = 0;
    };
}
