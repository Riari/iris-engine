#pragma once

#include <utility>
#include "InputBinding.hpp"
#include "InputEventHandler.hpp"

namespace Iris
{
    class MouseMoveEvent : public InputEventHandler
    {
    public:
        MouseMoveEvent(const Window &window, double x, double y) : InputEventHandler(window), m_x(x), m_y(y) {}

        [[nodiscard]] double GetX() const { return m_x; }
        [[nodiscard]] double GetY() const { return m_y; }

    private:
        double m_x;
        double m_y;
    };
}