#pragma once

#include <utility>

namespace OGL::Input
{
    class MouseScrollEvent
    {
    public:
        MouseScrollEvent(double x, double y) : m_x(x), m_y(y) {}

        [[nodiscard]] double GetX() const { return m_x; }
        [[nodiscard]] double GetY() const { return m_y; }

    private:
        double m_x;
        double m_y;
    };
}