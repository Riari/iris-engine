#include "State.hpp"

using namespace Iris;

State::State(Window &window, ImGuiLayer &imGuiLayer)
    : m_window(window), m_imGuiLayer(imGuiLayer) {}

Window &State::GetWindow()
{
    return m_window;
}

ImGuiLayer &State::GetImGuiLayer()
{
    return m_imGuiLayer;
}
