#include "Input/InputEventHandler.hpp"

using namespace Iris;

InputEventHandler::InputEventHandler(const Window &window) : m_window(window) {}

const Window& InputEventHandler::GetWindow()
{
    return m_window;
}
