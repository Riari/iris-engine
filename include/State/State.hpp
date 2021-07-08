#pragma once

#include <memory>

#include "Scene/Scene.hpp"
#include "Window/Window.hpp"
#include "ImGui/ImGuiLayer.hpp"

namespace Iris
{
    class State
    {
    public:
        State(Window&, Scene&, ImGuiLayer&);

        Window& GetWindow();
        Scene& GetScene();
        ImGuiLayer& GetImGuiLayer();

    private:
        Window& m_window;
        Scene& m_scene;
        ImGuiLayer& m_imGuiLayer;
    };
}