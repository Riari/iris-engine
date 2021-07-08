#pragma once

#include "ImGui/ImGuiWindow.hpp"

namespace Iris
{
    class TestWindow : public ImGuiWindow
    {
    public:
        void Build() override;
    };
}