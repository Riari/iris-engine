#include "Input/InputEventHandler.hpp"

using namespace OGL;

InputEventHandler::InputEventHandler(const Window &window) : m_window(window) {}

const Window& InputEventHandler::GetWindow()
{
    return m_window;
}
