#include "Input/InputEvent.hpp"

using namespace OGL;

InputEvent::InputEvent(const Window &window) : m_window(window) {}

const Window& InputEvent::GetWindow()
{
    return m_window;
}
