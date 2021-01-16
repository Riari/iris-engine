#pragma once

#include <utility>

#include "InputEvent.hpp"

namespace OGL
{
    class MouseScrollEvent : public InputEvent
    {
    public:
        MouseScrollEvent(const Window &window, double x, double y) : InputEvent(window), m_x(x), m_y(y) {}

        [[nodiscard]] double GetX() const { return m_x; }
        [[nodiscard]] double GetY() const { return m_y; }

    private:
        double m_x;
        double m_y;
    };
}