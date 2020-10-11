#pragma once

namespace OGL::Window
{
    class FrameBufferSizeHandler
    {
    public:
        virtual void OnFrameBufferSizeCallback(int width, int height) = 0;
    };
}
