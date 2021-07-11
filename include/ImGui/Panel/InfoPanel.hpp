#pragma once

#include "ImGui/ImGuiPanel.hpp"

namespace Iris
{
    class InfoPanel : public ImGuiPanel
    {
    public:
        void Build() override;
    };
}