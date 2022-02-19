#pragma once

#include <utility>
#include "InputEventHandler.hpp"

namespace Iris
{
    class MouseScrollEvent : public InputEventHandler
    {
    public:
        MouseScrollEvent(const Window &window, double x, double y) : InputEventHandler(window), m_x(x), m_y(y) {}

        [[nodiscard]] double GetX() const { return m_x; }
        [[nodiscard]] double GetY() const { return m_y; }

    private:
        double m_x;
        double m_y;
    };
}