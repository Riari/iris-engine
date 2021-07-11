#include "App/App.hpp"
#include "Demo/Keys.hpp"
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

void App::Handle(KeyEvent event)
{
    auto binding = event.GetBinding();
    if (binding == nullptr) return;

    if (binding->GetID() == Keys::ToggleDebug && event.GetAction() == GLFW_PRESS)
    {
        m_debug = !m_debug;
    }
}

void App::Run(const std::list<std::unique_ptr<State>>& states) const
{
    while (!m_shouldExit)
    {
        glfwPollEvents();

        for (auto const &state : states)
        {
            auto &window = state->GetWindow();
            auto &scene = state->GetScene();
            auto &imGuiLayer = state->GetImGuiLayer();

            if (m_debug) imGuiLayer.PrepareNewFrame();

            window.MakeCurrent();
            window.EnableVsync();

            window.Tick();

            if (window.ShouldUpdateFPS())
            {
                auto title = fmt::format("{} | {} FPS", window.GetTitle(), window.GetFrameCount());
                window.SetTitle(title.c_str());
                window.ResetFPSState();
            }

            while (window.ShouldUpdate())
            {
                for (const auto &system : m_updateSystems) system->Update(window, m_debug);
                window.OnUpdated();
            }

            if (m_debug) imGuiLayer.PrepareRender();

            Renderer::Clear(scene.GetClearColor());

            for (const auto &system : m_preRenderSystems) system->Update(window, scene, m_debug);
            for (const auto &system : m_renderSystems) system->Update(window, scene, m_debug);

            if (m_debug) imGuiLayer.Render();

            window.SwapBuffers();
            for (const auto &system : m_postRenderSystems) system->Update(window, scene, m_debug);
        }
    }
}
