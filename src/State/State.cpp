#include "State/State.hpp"

using namespace Iris;

State::State(Window& window, Scene& scene)
    : m_window(window), m_scene(scene) {}

Window &State::GetWindow()
{
    return m_window;
}

Scene &State::GetScene()
{
    return m_scene;
}
