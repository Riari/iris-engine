#include "Window/WindowEvent.hpp"

using namespace OGL;

WindowEvent::WindowEvent(const Window &window) : m_window(window) {}

const Window& WindowEvent::GetWindow()
{
    return m_window;
}
