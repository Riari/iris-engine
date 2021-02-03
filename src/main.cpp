#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <cxxopts.hpp>

#include "Demo/CameraController.hpp"
#include "Demo/ColoredCube.hpp"
#include "Demo/Keys.hpp"
#include "Demo/LightCube.hpp"
#include "Entity/EntityManager.hpp"

#if !defined(NDEBUG)
#include "GL/Debug.hpp"
#endif

using namespace IrisDemo;

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

    Iris::Logger::Init();

    glfwInit();
    glfwSetErrorCallback([](int error_code, const char* description) { Iris::Logger::GL->error(description); });

    const int display = opts["display"].as<int>();
    const int horizontalRes = opts["hres"].as<int>();
    const int verticalRes = opts["vres"].as<int>();
    const double fpsCap = opts["fpscap"].as<double>();

    Iris::WindowManager& windowManager = Iris::WindowManager::GetInstance();
    Iris::Window& mainWindow = windowManager.Create(0, "Iris Engine", display, horizontalRes, verticalRes, fpsCap);
    mainWindow.MakeCurrent();

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        Iris::Logger::MAIN->critical("Failed to initialize GLAD");
        return -1;
    }

    Iris::Logger::MAIN->info("GLAD initialized");

#if !defined(NDEBUG)
    InitGLDebug();
#endif

    Iris::InputManager::RegisterBinding(Keys::MoveForward, GLFW_KEY_W);
    Iris::InputManager::RegisterBinding(Keys::MoveBackward, GLFW_KEY_S);
    Iris::InputManager::RegisterBinding(Keys::StrafeLeft, GLFW_KEY_A);
    Iris::InputManager::RegisterBinding(Keys::StrafeRight, GLFW_KEY_D);
    Iris::InputManager::RegisterBinding(Keys::Ascend, GLFW_KEY_SPACE);
    Iris::InputManager::RegisterBinding(Keys::Descend, GLFW_KEY_C);

    Iris::WindowManager::RegisterHandler<Iris::FrameBufferEvent>([](const Iris::FrameBufferEvent& event) { Renderer::SetViewport(event.GetWidth(), event.GetHeight()); });

    auto bufferSize = mainWindow.GetFramebufferSize();
    Renderer::SetViewport(bufferSize[0], bufferSize[1]);

    auto pCamera = std::make_shared<Iris::Camera>(mainWindow.GetAspectRatio(), glm::vec3(-0.8f, 0.0f, 12.0f));
    pCamera->SetRotateSpeed(5);
    auto pCameraController = std::make_shared<CameraController>(0, pCamera);

    auto pScene = std::make_shared<Scene>(0);
    pScene->SetActiveCamera(pCamera);
    pScene->AddController(pCameraController);

    float cubeVertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    auto pCubeVBO = new VBO();
    pCubeVBO->Bind();
    pCubeVBO->SetData(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    Iris::EntityManager& entityManager = Iris::EntityManager::GetInstance();

    auto pLightCube = entityManager.CreateEntity<LightCube>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    pLightCube->GetTransform().SetScale(0.1f);

    auto pColoredCube = entityManager.CreateEntity<ColoredCube>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.1f, 0.2f), pLightCube);
    pColoredCube->GetTransform().SetRotation(135.0f);
    pColoredCube->GetTransform().SetScale(glm::vec3(0.8f, 1.0f, 1.2f));

    auto pColoredCube2 = entityManager.CreateEntity<ColoredCube>(glm::vec3(2.0f, 1.0f, -1.0f), glm::vec3(0.2f, 1.0f, 0.3f), pLightCube);
    pColoredCube2->GetTransform().SetRotation(185.0f);
    pColoredCube2->GetTransform().SetScale(glm::vec3(1.8f, 1.0f, -1.2f));

    pScene->AddEntities(entityManager.GetEntities());

    mainWindow.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mainWindow.SetScene(pScene);

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

    delete pCubeVBO;

    return 0;
}