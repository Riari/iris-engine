#include "State/State.hpp"

using namespace Iris;

State::State(Window& window, Scene& scene, ImGuiLayer& imGuiLayer)
    : m_window(window), m_scene(scene), m_imGuiLayer(imGuiLayer) {}

Window &State::GetWindow()
{
    return m_window;
}

Scene &State::GetScene()
{
    return m_scene;
}

ImGuiLayer &State::GetImGuiLayer()
{
    return m_imGuiLayer;
}
