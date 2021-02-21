#include <random>

#include <glad/glad.h>

#include "Demo/MainScene.hpp"
#include "Entity/Component/Camera.hpp"
#include "Entity/Component/Mesh.hpp"
#include "Entity/Component/PointLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "Entity/EntityManager.hpp"
#include "GL/Renderer.hpp"
#include "System/SystemManager.hpp"
#include "Utility/Logger.hpp"

using namespace Iris;

void MainScene::Setup(float aspectRatio)
{
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

    auto pCubeVBO = std::make_shared<VBO>();
    pCubeVBO->Bind();
    pCubeVBO->SetData(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    EntityManager& entityManager = EntityManager::GetInstance();
    ComponentManager& componentManager = ComponentManager::GetInstance();
    SystemManager& systemManager = SystemManager::GetInstance();

    componentManager.RegisterComponentType<Camera>();
    componentManager.RegisterComponentType<Mesh>();
    componentManager.RegisterComponentType<PointLight>();
    componentManager.RegisterComponentType<Transform>();

    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPosition(-3.0f, 3.0f);
    std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
    std::uniform_real_distribution<float> randScale(0.5f, 2.0f);
    std::uniform_real_distribution<float> randColor(0.0f, 1.0f);

    m_cameraController = systemManager.RegisterSystem<CameraController>();
    m_meshRenderer = systemManager.RegisterSystem<MeshRenderer>();
    m_lightingDemo = systemManager.RegisterSystem<LightingDemo>();

    auto pVao = std::make_shared<VAO>();
    pVao->Bind();
    VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    VBO::SetVertexAttribute(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO::Unbind();

    auto pProgram = std::make_shared<ShaderProgram>("ColoredCube", Logger::GL);
    pProgram->Build();
    pProgram->Use();

    for (int i = 0; i < 5; i++)
    {
        auto id = entityManager.CreateEntity();
        componentManager.AddComponent(id, Transform{
                .position = glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
                .rotation = randRotation(generator),
                .scale = glm::vec3(randScale(generator), randScale(generator), randScale(generator))
        });
        componentManager.AddComponent(id, Mesh{
                .pVbo = pCubeVBO,
                .pVao = pVao,
                .pShaderProgram = pProgram,
                .color = glm::vec3(randColor(generator), randColor(generator), randColor(generator))
        });
    }

    auto cameraId = entityManager.CreateEntity();
    componentManager.AddComponent(cameraId, Camera{
            .position = glm::vec3(-0.8f, 0.0f, 12.0f),
            .aspectRatio = aspectRatio
    });

    m_cameraController->SetActiveCameraId(cameraId);

    auto lightId = entityManager.CreateEntity();
    componentManager.AddComponent(lightId, Transform{
            .position = glm::vec3(0.0f, 0.0f, 0.0f),
            .rotation = 0.0f,
            .scale = glm::vec3(0.1f, 0.1f, 0.1f)
    });

    auto pLightVao = std::make_shared<VAO>();
    pLightVao->Bind();
    VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    VAO::Unbind();

    auto pLightProgram = std::make_shared<ShaderProgram>("LightSource", Logger::GL);
    pLightProgram->Build();
    pLightProgram->Use();

    componentManager.AddComponent(lightId, Mesh{
            .pVbo = pCubeVBO,
            .pVao = pLightVao,
            .pShaderProgram = pLightProgram,
            .color = glm::vec3(1.0f, 1.0f, 1.0f)
    });
    componentManager.AddComponent(lightId, PointLight{
            .color = glm::vec3(1.0f, 1.0f, 1.0f)
    });

    m_meshRenderer->SetPointLightId(lightId);
    m_meshRenderer->SetActiveCameraId(cameraId);
}

void MainScene::Update(Window &window)
{
    m_cameraController->Update(window);
    m_lightingDemo->Update(window);
}

void MainScene::Render(Window &window)
{
    Renderer::Clear();
    m_meshRenderer->Update(window);
    window.SwapBuffers();
}

void MainScene::Teardown()
{

}
