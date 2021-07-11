#include "Asset/AssetManager.hpp"
#include "Entity/Component/Camera.hpp"
#include "Entity/Component/SpotLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "Scene/Scene.hpp"
#include "System/SpotLightController.hpp"

using namespace Iris;

std::list<ComponentType> SpotLightController::GetComponentTypes()
{
    return {
            GetComponentType<Transform>(),
            GetComponentType<SpotLight>()
    };
}

void SpotLightController::SetCameraId(EntityId id)
{
    m_cameraId = id;
}

void SpotLightController::Update(Window &window, Scene& scene, bool debug)
{
    auto sceneEntities = scene.GetEntities();
    auto& camera = GetComponent<Camera>(m_cameraId);

    AssetManager& assetManager = AssetManager::GetInstance();
    auto materialShaderProgram = assetManager.GetShaderProgram("Material");
    materialShaderProgram->Use();

    int i = 0;
    for (auto const& id : m_entities)
    {
        // TODO: find a better way of limiting the update to the intersection of system and scene entities
        if (sceneEntities.find(id) == sceneEntities.end()) continue;

        auto& transform = GetComponent<Transform>(id);
        auto& spotLight = GetComponent<SpotLight>(id);

        // For demo purposes while there's only one spot light defined.
        // This kind of thing should be handled via scene graph traversal
        transform.position = camera.position;
        spotLight.direction = camera.front;

        auto key = "spotLights[" + std::to_string(i) + "].";
        materialShaderProgram->SetUniform3f(key + "position", transform.position);
        materialShaderProgram->SetUniform3f(key + "ambient", spotLight.ambient);
        materialShaderProgram->SetUniform3f(key + "diffuse", spotLight.diffuse);
        materialShaderProgram->SetUniform3f(key + "specular", spotLight.specular);
        materialShaderProgram->SetUniform3f(key + "direction", spotLight.direction);
        materialShaderProgram->SetUniformFloat(key + "innerEdge", spotLight.innerEdge);
        materialShaderProgram->SetUniformFloat(key + "outerEdge", spotLight.outerEdge);
        materialShaderProgram->SetUniformFloat(key + "constant", spotLight.constant);
        materialShaderProgram->SetUniformFloat(key + "linear", spotLight.linear);
        materialShaderProgram->SetUniformFloat(key + "quadratic", spotLight.quadratic);

        i++;
    }

    materialShaderProgram->SetUniformInt("spotLightCount", i);
}
