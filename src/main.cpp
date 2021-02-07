#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <cxxopts.hpp>

#include "Demo/Keys.hpp"
#include "Demo/MainScene.hpp"
#include "GL/Renderer.hpp"
#include "Input/InputManager.hpp"
#include "System/CameraController.hpp"

#if !defined(NDEBUG)
#include "GL/Debug.hpp"
#endif

using namespace Iris;

int main(int argc, char** argv)
{
    cxxopts::Options options("IrisEngine", "");

    options.add_options()
            ("d,display", "Display # to use (launches as window if unspecified)", cxxopts::value<int>()->default_value("-1"))
            ("h,hres", "Horizontal screen resolution", cxxopts::value<int>()->default_value("1920"))
            ("v,vres", "Vertical screen resolution", cxxopts::value<int>()->default_value("1080"))
            ("f,fpscap", "FPS cap", cxxopts::value<double>()->default_value("60"))
    ;

    auto opts = options.parse(argc, argv);

    Logger::Init();

    glfwInit();
    glfwSetErrorCallback([](int error_code, const char* description) { Logger::GL->error(description); });

    const int display = opts["display"].as<int>();
    const int horizontalRes = opts["hres"].as<int>();
    const int verticalRes = opts["vres"].as<int>();
    const double fpsCap = opts["fpscap"].as<double>();

    WindowManager& windowManager = WindowManager::GetInstance();
    Window& mainWindow = windowManager.Create(0, "Iris Engine", display, horizontalRes, verticalRes, fpsCap);
    mainWindow.MakeCurrent();

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        Iris::Logger::MAIN->critical("Failed to initialize GLAD");
        return -1;
    }

    Logger::MAIN->info("GLAD initialized");

#if !defined(NDEBUG)
    InitGLDebug();
#endif

    InputManager::RegisterBinding(Keys::MoveForward, GLFW_KEY_W);
    InputManager::RegisterBinding(Keys::MoveBackward, GLFW_KEY_S);
    InputManager::RegisterBinding(Keys::StrafeLeft, GLFW_KEY_A);
    InputManager::RegisterBinding(Keys::StrafeRight, GLFW_KEY_D);
    InputManager::RegisterBinding(Keys::Ascend, GLFW_KEY_SPACE);
    InputManager::RegisterBinding(Keys::Descend, GLFW_KEY_C);

    WindowManager::RegisterHandler<FrameBufferEvent>([](const FrameBufferEvent& event) { Renderer::SetViewport(event.GetWidth(), event.GetHeight()); });

    auto bufferSize = mainWindow.GetFramebufferSize();
    Renderer::SetViewport(bufferSize[0], bufferSize[1]);

    mainWindow.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mainWindow.SetScene(std::make_shared<MainScene>());

    Renderer::EnableCapability(GL_DEPTH_TEST);

    while (!windowManager.GetWindows().empty())
    {
        glfwPollEvents();

        for (auto const& [id, window] : windowManager.GetWindows())
        {
            window->MakeCurrent();
            window->EnableVsync();
            window->Update();

            if (window->ShouldClose()) windowManager.Destroy(id);
        }
    }

    return 0;
}