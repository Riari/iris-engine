#include <imgui.h>

#include "ImGui/Window/TestWindow.hpp"

using namespace Iris;

void TestWindow::Build()
{
    ImGui::Begin("Hello, world!");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
