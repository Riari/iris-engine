#pragma once

#include "WindowEvent.hpp"

namespace Iris
{
    class Window;

    class FrameBufferEvent : public WindowEvent
    {
    public:
        FrameBufferEvent(const Window &window, int w, int h) : WindowEvent(window), m_width(w), m_height(h) {}

        [[nodiscard]] int GetWidth() const { return m_width; }
        [[nodiscard]] int GetHeight() const { return m_height; }

    private:
        int m_width;
        int m_height;
    };
}