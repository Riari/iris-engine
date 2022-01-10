#include "Asset/AssetManager.hpp"
#include "Entity/Component/PointLightComponent.hpp"
#include "Entity/Component/TransformComponent.hpp"
#include "Scene/Scene.hpp"
#include "System/PointLightController.hpp"

using namespace Iris;

std::list<ComponentType> PointLightController::GetComponentTypes()
{
    return {
        GetComponentType<TransformComponent>(),
        GetComponentType<PointLightComponent>()
    };
}

void PointLightController::Update(Window &window, Scene& scene, bool debug)
{
    auto sceneEntities = scene.GetEntities();

    AssetManager& assetManager = AssetManager::GetInstance();
    auto materialShaderProgram = assetManager.GetShaderProgram("Material");
    materialShaderProgram->Use();

    int i = 0;
    for (auto const& id : m_entities)
    {
        // TODO: find a better way of limiting the update to the intersection of system and scene entities
        if (sceneEntities.find(id) == sceneEntities.end()) continue;

        auto& transform = GetComponent<TransformComponent>(id);
        auto& pointLight = GetComponent<PointLightComponent>(id);

        auto key = "pointLights[" + std::to_string(i) + "].";
        materialShaderProgram->SetUniform3f(key + "position", transform.position);
        materialShaderProgram->SetUniform3f(key + "ambient", pointLight.ambient);
        materialShaderProgram->SetUniform3f(key + "diffuse", pointLight.diffuse);
        materialShaderProgram->SetUniform3f(key + "specular", pointLight.specular);
        materialShaderProgram->SetUniformFloat(key + "constant", pointLight.constant);
        materialShaderProgram->SetUniformFloat(key + "linear", pointLight.linear);
        materialShaderProgram->SetUniformFloat(key + "quadratic", pointLight.quadratic);

        i++;
    }

    materialShaderProgram->SetUniformInt("pointLightCount", i);
}
