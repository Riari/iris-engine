#include <imgui.h>

#include "Entity/Component/CameraComponent.hpp"
#include "Entity/ComponentManager.hpp"
#include "ImGui/Panel/InfoPanel.hpp"

using namespace Iris;

InfoPanel::InfoPanel(EntityId mainCameraId) : m_mainCameraId(mainCameraId) {}

void InfoPanel::Build()
{
    // TODO: make this better
    ComponentManager& componentManager = ComponentManager::GetInstance();
    auto& camera = componentManager.GetComponent<CameraComponent>(m_mainCameraId);

    ImGui::Begin("Info");

    ImGui::Text("Performance");
    ImGui::Separator();
    ImGui::Text("Frame time: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Spacing();

    ImGui::Text("CameraComponent");
    ImGui::Separator();
    ImGui::Text("Position: (%.3f, %.3f, %.3f)", camera.position[0], camera.position[1], camera.position[2]);
    ImGui::Text("Front: (%.3f, %.3f, %.3f)", camera.front[0], camera.front[1], camera.front[2]);
    ImGui::Text("Yaw: %.3f, Pitch: %.3f", camera.yaw, camera.pitch);
    ImGui::Text("FOV: %.3f", camera.fov);

    ImGui::End();
}
