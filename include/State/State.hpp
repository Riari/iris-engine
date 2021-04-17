#pragma once

#include <memory>

#include "Scene/Scene.hpp"
#include "Window/Window.hpp"

namespace Iris
{
    class State
    {
    public:
        State(Window&, Scene&);

        Window& GetWindow();
        Scene& GetScene();

    private:
        Window& m_window;
        Scene& m_scene;
    };
}