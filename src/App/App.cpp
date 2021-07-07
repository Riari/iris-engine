#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "App/App.hpp"
#include "GL/Renderer.hpp"

using namespace Iris;

App &App::GetInstance()
{
    static App instance;
    return instance;
}

void App::RegisterUpdateSystem(const std::shared_ptr<System>& system)
{
    m_updateSystems.push_back(system);
}

void App::RegisterPreRenderSystem(const std::shared_ptr<System>& system)
{
    m_preRenderSystems.push_back(system);
}

void App::RegisterRenderSystem(const std::shared_ptr<System>& system)
{
    m_renderSystems.push_back(system);
}

void App::RegisterPostRenderSystem(const std::shared_ptr<System>& system)
{
    m_postRenderSystems.push_back(system);
}

void App::Run(const std::list<std::unique_ptr<State>>& states) const
{
    // TODO: Clean this up
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!m_shouldExit)
    {
        glfwPollEvents();

        // TODO: Clean this up
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");

            ImGui::Text("This is some useful text.");
            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            if (ImGui::Button("Button")) counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me")) show_another_window = false;
            ImGui::End();
        }

        for (auto const& state : states)
        {
            auto& window = state->GetWindow();
            auto& scene = state->GetScene();

            window.MakeCurrent();
            window.EnableVsync();

            window.Tick();

            if (window.ShouldUpdateFPS()) {
                auto title = fmt::format("{} | {} FPS", window.GetTitle(), window.GetFrameCount());
                window.SetTitle(title.c_str());
                window.ResetFPSState();
            }

            while (window.ShouldUpdate())
            {
                for (const auto& system : m_updateSystems) system->Update(window.GetDeltaTime());
                window.OnUpdated();
            }

            ImGui::Render();

            Renderer::Clear(scene.GetClearColor());

            for (const auto& system : m_preRenderSystems) system->Update(window, scene);
            for (const auto& system : m_renderSystems) system->Update(window, scene);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            window.SwapBuffers();
            for (const auto& system : m_postRenderSystems) system->Update(window, scene);
        }
    }

    // TODO: Clean this up
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
