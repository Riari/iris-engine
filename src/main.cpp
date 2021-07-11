#include <memory>
#include <random>

#include <glm/glm.hpp>
#include <cxxopts.hpp>

#include "App/App.hpp"
#include "Asset/AssetManager.hpp"
#include "Demo/Keys.hpp"
#include "Entity/Component/Camera.hpp"
#include "Entity/Component/Material.hpp"
#include "Entity/Component/Mesh.hpp"
#include "Entity/Component/DirectionalLight.hpp"
#include "Entity/Component/PointLight.hpp"
#include "Entity/Component/SpotLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "Entity/EntityManager.hpp"
#include "GL/Renderer.hpp"
#include "GL/Texture.hpp"
#include "ImGui/ImGuiLayer.hpp"
#include "ImGui/Panel/InfoPanel.hpp"
#include "Input/InputManager.hpp"
#include "Scene/Scene.hpp"
#include "Scene/SceneManager.hpp"
#include "State/State.hpp"
#include "System/CameraController.hpp"
#include "System/MeshRenderer.hpp"
#include "System/PointLightController.hpp"
#include "System/SpotLightController.hpp"
#include "System/SystemManager.hpp"
#include "Window/FrameBufferEvent.hpp"
#include "Window/WindowManager.hpp"

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

    ImGuiLayer imGuiLayer = ImGuiLayer();
    imGuiLayer.AttachPanel(std::make_unique<InfoPanel>());
    imGuiLayer.Init(mainWindow.GetGLFWWindow());

    InputManager::RegisterBinding(Keys::MoveForward, GLFW_KEY_W);
    InputManager::RegisterBinding(Keys::MoveBackward, GLFW_KEY_S);
    InputManager::RegisterBinding(Keys::StrafeLeft, GLFW_KEY_A);
    InputManager::RegisterBinding(Keys::StrafeRight, GLFW_KEY_D);
    InputManager::RegisterBinding(Keys::Ascend, GLFW_KEY_SPACE);
    InputManager::RegisterBinding(Keys::Descend, GLFW_KEY_C);
    InputManager::RegisterBinding(Keys::ToggleDebug, GLFW_KEY_H);

    WindowManager::RegisterHandler<FrameBufferEvent>([](const FrameBufferEvent& event) { Renderer::SetViewport(event.GetWidth(), event.GetHeight()); });

    auto bufferSize = mainWindow.GetFramebufferSize();
    Renderer::SetViewport(bufferSize[0], bufferSize[1]);

    mainWindow.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Renderer::EnableCapability(GL_DEPTH_TEST);

    float cubeVertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    auto pCubeVBO = std::make_shared<VBO>();
    pCubeVBO->Bind();
    pCubeVBO->SetData(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    EntityManager& entityManager = EntityManager::GetInstance();
    ComponentManager& componentManager = ComponentManager::GetInstance();
    SystemManager& systemManager = SystemManager::GetInstance();

    componentManager.RegisterComponentType<Camera>();
    componentManager.RegisterComponentType<Material>();
    componentManager.RegisterComponentType<Mesh>();
    componentManager.RegisterComponentType<DirectionalLight>();
    componentManager.RegisterComponentType<PointLight>();
    componentManager.RegisterComponentType<SpotLight>();
    componentManager.RegisterComponentType<Transform>();

    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPositionX(-6.0f, 6.0f);
    std::uniform_real_distribution<float> randPosition(-3.0f, 3.0f);
    std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
    std::uniform_real_distribution<float> randScale(0.2f, 2.0f);
    std::uniform_real_distribution<float> randColor(0.0f, 1.0f);

    auto cameraController = systemManager.RegisterSystem<CameraController>();
    auto pointLightController = systemManager.RegisterSystem<PointLightController>();
    auto spotLightController = systemManager.RegisterSystem<SpotLightController>();
    auto meshRenderer = systemManager.RegisterSystem<MeshRenderer>();

    App& app = App::GetInstance();
    app.RegisterUpdateSystem(cameraController);
    app.RegisterPreRenderSystem(pointLightController);
    app.RegisterPreRenderSystem(spotLightController);
    app.RegisterRenderSystem(meshRenderer);

    auto pCubeVao = std::make_shared<VAO>();
    pCubeVao->Bind();
    VBO::SetVertexAttribute(0, 3, 8 * sizeof(float), (void*)0);
    VBO::SetVertexAttribute(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VBO::SetVertexAttribute(2, 2, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO::Unbind();

    AssetManager& assetManager = AssetManager::GetInstance();

    std::shared_ptr<Texture> containerDiffuseTexture = assetManager.GenerateTexture("assets/textures/container_diffuse.png");
    std::shared_ptr<Texture> containerSpecularTexture = assetManager.GenerateTexture("assets/textures/container_specular.png");
    std::shared_ptr<Texture> containerEmissionTexture = assetManager.GenerateTexture("assets/textures/container_emission.jpg");

    Scene& mainScene = SceneManager::GetInstance().Create(1);
    mainScene.SetClearColor(glm::vec4(0.1f, 0.1f, 0.14f, 1.0f));

    for (int i = 0; i < 20; i++)
    {
        auto id = entityManager.CreateEntity();
        mainScene.AddEntity(id);
        auto transformScale = randScale(generator);
        componentManager.AddComponent(id, Transform{
                .position = glm::vec3(randPositionX(generator), randPosition(generator), randPosition(generator)),
                .rotation = randRotation(generator),
                .scale = glm::vec3(transformScale, transformScale, transformScale),
        });
        componentManager.AddComponent(id, Mesh{
                .pVbo = pCubeVBO,
                .pVao = pCubeVao,
        });
        componentManager.AddComponent(id, Material{
                .pDiffuseMap = containerDiffuseTexture,
                .pSpecularMap = containerSpecularTexture,
                .pEmissionMap = containerEmissionTexture,
                .shininess = 32.0f,
        });
    }

    auto cameraId = entityManager.CreateEntity();
    mainScene.AddEntity(cameraId);
    componentManager.AddComponent(cameraId, Camera{
            .position = glm::vec3(-0.8f, 0.0f, 12.0f),
            .aspectRatio = mainWindow.GetAspectRatio(),
    });

    cameraController->SetActiveCameraId(cameraId);

    auto pPointLightVao = std::make_shared<VAO>();
    pPointLightVao->Bind();
    VBO::SetVertexAttribute(0, 3, 8 * sizeof(float), (void*)0);
    VAO::Unbind();

    auto directionalLightId = entityManager.CreateEntity();
    mainScene.AddEntity(directionalLightId);
    componentManager.AddComponent(directionalLightId, Transform{
            .position = glm::vec3(0.0f, 0.0f, 0.0f),
            .rotation = 0.0f,
            .scale = glm::vec3(0.1f, 0.1f, 0.1f),
    });
    componentManager.AddComponent(directionalLightId, Mesh{
            .pVbo = pCubeVBO,
            .pVao = pPointLightVao,
            .color = glm::vec3(0.0f, 0.0f, 0.0f),
    });
    componentManager.AddComponent(directionalLightId, Material{});
    componentManager.AddComponent(directionalLightId, DirectionalLight{
            .ambient = glm::vec3(0.02f, 0.02f, 0.02f),
            .diffuse = glm::vec3(0.4f, 0.1f, 0.1f),
            .specular = glm::vec3(0.4f, 0.1f, 0.1f),
            .direction = glm::vec3(-0.2f, -1.0f, -0.3f),
    });

    for (int i = 0; i < 6; i++)
    {
        auto pointLightId = entityManager.CreateEntity();
        mainScene.AddEntity(pointLightId);
        componentManager.AddComponent(pointLightId, Transform{
                .position = glm::vec3(randPositionX(generator), randPosition(generator), randPosition(generator)),
                .rotation = 0.0f,
                .scale = glm::vec3(0.1f, 0.1f, 0.1f),
        });
        componentManager.AddComponent(pointLightId, Mesh{
                .pVbo = pCubeVBO,
                .pVao = pPointLightVao,
                .color = glm::vec3(1.0f, 1.0f, 1.0f)
        });
        componentManager.AddComponent(pointLightId, Material{});
        componentManager.AddComponent(pointLightId, PointLight{
                .ambient = glm::vec3(0.05f, 0.05f, 0.05f),
                .diffuse = glm::vec3(0.2f, 0.2f, 0.2f),
                .specular = glm::vec3(0.5f, 0.5f, 0.5f),
                .constant = 1.0f,
                .linear = 0.09f,
                .quadratic = 0.032f,
        });
    }

    auto spotLightId = entityManager.CreateEntity();
    mainScene.AddEntity(spotLightId);
    componentManager.AddComponent(spotLightId, Transform{
            .position = glm::vec3(0.0f, 0.0f, 0.0f),
            .rotation = 0.0f,
            .scale = glm::vec3(0.01f, 0.01f, 0.01f),
    });

    componentManager.AddComponent(spotLightId, Mesh{
            .pVbo = pCubeVBO,
            .pVao = pPointLightVao,
            .color = glm::vec3(0.0f, 0.0f, 0.0f),
    });
    componentManager.AddComponent(spotLightId, Material{});
    componentManager.AddComponent(spotLightId, SpotLight{
            .ambient = glm::vec3(0.6f, 0.6f, 0.4f),
            .diffuse = glm::vec3(1.0f, 1.0f, 0.8f),
            .specular = glm::vec3(1.0f, 1.0f, 1.0f),
            .innerEdge = glm::cos(glm::radians(12.5f)),
            .outerEdge = glm::cos(glm::radians(17.5f)),
            .constant = 1.0f,
            .linear = 0.09f,
            .quadratic = 0.032f,
    });

    meshRenderer->SetDirectionalLightId(directionalLightId);
    meshRenderer->SetActiveCameraId(cameraId);

    // For demo purposes while there's only one spot light defined.
    spotLightController->SetCameraId(cameraId);

    std::list<std::unique_ptr<State>> states;
    states.push_back(std::make_unique<State>(mainWindow, mainScene, imGuiLayer));

    app.Run(states);

    imGuiLayer.Cleanup();

    return 0;
}