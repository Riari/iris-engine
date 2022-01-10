#include <imgui.h>

#include "Entity/Component/PointLightComponent.hpp"
#include "Entity/Component/TransformComponent.hpp"
#include "Entity/ComponentManager.hpp"
#include "ImGui/Panel/PointLightControlPanel.hpp"
#include "System/PointLightController.hpp"
#include "System/SystemManager.hpp"

using namespace Iris;

void PointLightControlPanel::Build()
{
    // TODO: make this better
    ComponentManager& componentManager = ComponentManager::GetInstance();
    SystemManager& systemManager = SystemManager::GetInstance();
    auto pPointLightController = systemManager.GetSystem<PointLightController>();
    auto pointLights = pPointLightController->GetEntities();

    ImGui::Begin("Point Lights");

    {
        ImGui::BeginChild("select", ImVec2(150, 0), true);

        for (auto const& id : pointLights)
        {
            if (ImGui::Selectable(std::to_string(id).c_str(), m_selected == id))
            {
                m_selected = id;

                auto transform = componentManager.GetComponent<TransformComponent>(id);
                auto pointLight = componentManager.GetComponent<PointLightComponent>(id);
                m_position[0] = transform.position[0];
                m_position[1] = transform.position[1];
                m_position[2] = transform.position[2];
                m_ambient[0] = pointLight.ambient[0];
                m_ambient[1] = pointLight.ambient[1];
                m_ambient[2] = pointLight.ambient[2];
                m_diffuse[0] = pointLight.diffuse[0];
                m_diffuse[1] = pointLight.diffuse[1];
                m_diffuse[2] = pointLight.diffuse[2];
                m_specular[0] = pointLight.specular[0];
                m_specular[1] = pointLight.specular[1];
                m_specular[2] = pointLight.specular[2];
            }
        }

        ImGui::EndChild();
    }

    ImGui::SameLine();

    if (m_selected > 0)
    {
        auto& transform = componentManager.GetComponent<TransformComponent>(m_selected);
        auto& pointLight = componentManager.GetComponent<PointLightComponent>(m_selected);

        ImGui::BeginGroup();
        ImGui::BeginChild("edit", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
        ImGui::Text("Properties (%d)", m_selected);
        ImGui::Separator();

        if (ImGui::SliderFloat3("Position", m_position, -30.0f, 30.0f))
        {
            transform.position = glm::vec3(m_position[0], m_position[1], m_position[2]);
        }

        if (ImGui::ColorEdit3("Ambient", m_ambient))
        {
            pointLight.ambient = glm::vec3(m_ambient[0], m_ambient[1], m_ambient[2]);
        }

        if (ImGui::ColorEdit3("Diffuse", m_diffuse))
        {
            pointLight.diffuse = glm::vec3(m_diffuse[0], m_diffuse[1], m_diffuse[2]);
        }

        if (ImGui::ColorEdit3("Specular", m_specular))
        {
            pointLight.specular = glm::vec3(m_specular[0], m_specular[1], m_specular[2]);
        }

        ImGui::EndChild();
        ImGui::EndGroup();
    }

    ImGui::End();
}
