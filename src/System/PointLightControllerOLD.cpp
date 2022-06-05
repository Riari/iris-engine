// #include "Asset/AssetManager.hpp"
// #include "Entity/Component/PointLight.hpp"
// #include "Entity/Component/Transform.hpp"
// #include "PointLightController.hpp"

// using namespace Iris::OLD;

// std::list<ComponentType> PointLightController::GetComponentTypes()
// {
//     return {
//         GetComponentType<TransformComponent>(),
//         GetComponentType<PointLightComponent>()
//     };
// }

// void PointLightController::Update(Window &window, Scene& scene, bool debug)
// {
//     auto sceneEntities = scene.GetEntities();

//     AssetManager& assetManager = AssetManager::GetInstance();
//     auto program = assetManager.GetShaderProgram("Material");
//     program->Use();

//     int i = 0;
//     for (auto const& id : m_entities)
//     {
//         // TODO: find a better way of limiting the update to the intersection of system and scene entities
//         if (sceneEntities.find(id) == sceneEntities.end()) continue;

//         auto& transform = GetComponent<TransformComponent>(id);
//         auto& pointLight = GetComponent<PointLightComponent>(id);

//         auto key = "pointLights[" + std::to_string(i) + "].";
//         program->SetUniform3f(key + "position", transform.position);
//         program->SetUniform3f(key + "ambient", pointLight.ambient);
//         program->SetUniform3f(key + "diffuse", pointLight.diffuse);
//         program->SetUniform3f(key + "specular", pointLight.specular);
//         program->SetUniformFloat(key + "constant", pointLight.constant);
//         program->SetUniformFloat(key + "linear", pointLight.linear);
//         program->SetUniformFloat(key + "quadratic", pointLight.quadratic);

//         i++;
//     }

//     program->SetUniformInt("pointLightCount", i);
// }
