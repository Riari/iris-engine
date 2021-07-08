#pragma once

#include <list>
#include <memory>

#include <GLFW/glfw3.h>

#include "ImGuiWindow.hpp"

namespace Iris
{
    class ImGuiLayer
    {
    public:
        void Init(GLFWwindow*);

        void AttachWindow(std::unique_ptr<ImGuiWindow>);

        void PrepareNewFrame();
        void PrepareRender();
        void Render();

        void Cleanup();

    private:
        std::list<std::unique_ptr<ImGuiWindow>> m_windows;
    };
}