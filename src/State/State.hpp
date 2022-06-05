#pragma once

#include <memory>
#include "ImGui/ImGuiLayer.hpp"
#include "Window/Window.hpp"

namespace Iris
{
    class State
    {
    public:
        State(Window &, ImGuiLayer &);

        Window &GetWindow();
        ImGuiLayer &GetImGuiLayer();

    private:
        Window &m_window;
        ImGuiLayer &m_imGuiLayer;
    };
}
