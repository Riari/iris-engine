#pragma once

namespace OGL::Window
{
    class CursorPosHandler
    {
    public:
        virtual void OnCursorPosCallback(double x, double y) = 0;
    };
}
