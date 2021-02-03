#include "Window/WindowEvent.hpp"

using namespace Iris;

WindowEvent::WindowEvent(const Window &window) : m_window(window) {}

const Window& WindowEvent::GetWindow()
{
    return m_window;
}
