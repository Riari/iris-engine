#pragma once

#include <utility>

#include "InputBinding.h"

namespace OGL::Input
{
    class MouseMoveEvent
    {
    public:
        MouseMoveEvent(double x, double y) : m_x(x), m_y(y) {}

        [[nodiscard]] double GetX() const { return m_x; }
        [[nodiscard]] double GetY() const { return m_y; }

    private:
        double m_x;
        double m_y;
    };
}