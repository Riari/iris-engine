#include <imgui.h>

#include "Entity/Component/Transform.hpp"
#include "Entity/ComponentManager.hpp"
#include "ImGui/Panel/InfoPanel.hpp"
#include "System/PointLightController.hpp"
#include "System/SystemManager.hpp"

using namespace Iris;

void InfoPanel::Build()
{
    // TODO: make this better
    ComponentManager& componentManager = ComponentManager::GetInstance();
    SystemManager& systemManager = SystemManager::GetInstance();
    auto pPointLightController = systemManager.GetSystem<PointLightController>();
    auto pointLights = pPointLightController->GetEntities();

    ImGui::Begin("Info");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    int i = 0;
    for (auto const& id : pointLights)
    {
        auto& transform = componentManager.GetComponent<Transform>(id);

        ImGui::Text("Point light %", i++);
    }

    ImGui::End();
}
