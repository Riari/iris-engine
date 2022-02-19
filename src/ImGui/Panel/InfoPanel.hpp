#pragma once

#include "Entity/Entity.hpp"
#include "ImGui/ImGuiPanel.hpp"

namespace Iris
{
    class InfoPanel : public ImGuiPanel
    {
    public:
        InfoPanel(EntityId mainCameraId);
        void Build() override;

    private:
        EntityId m_mainCameraId;
    };
}