#pragma once

#include "Entity/Entity.hpp"
#include "ImGui/ImGuiPanel.hpp"

namespace Iris
{
    class PointLightControlPanel : public ImGuiPanel
    {
    public:
        void Build() override;

    private:
        EntityId m_selected = 0;
        float m_position[3]{};
        float m_ambient[3]{};
        float m_diffuse[3]{};
        float m_specular[3]{};
    };
}