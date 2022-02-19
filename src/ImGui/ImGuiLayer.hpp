#pragma once

#include <list>
#include <memory>
#include <GLFW/glfw3.h>
#include "Window/Window.hpp"
#include "ImGuiPanel.hpp"

namespace Iris
{
    class ImGuiLayer
    {
    public:
        void Init(GLFWwindow*);

        void AttachPanel(std::unique_ptr<ImGuiPanel> panel);

        void PrepareNewFrame();
        void PrepareRender();
        void Render();

        void Cleanup();

    private:
        std::list<std::unique_ptr<ImGuiPanel>> m_panels;
    };
}