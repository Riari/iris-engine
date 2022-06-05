// #include "Asset/AssetManager.hpp"
// #include "Entity/Component/Camera.hpp"
// #include "Entity/Component/SpotLight.hpp"
// #include "Entity/Component/Transform.hpp"
// #include "Scene/Scene.hpp"
// #include "SpotLightController.hpp"

// using namespace Iris::OLD;

// std::list<ComponentType> SpotLightController::GetComponentTypes()
// {
//     return {
//         GetComponentType<TransformComponent>(),
//         GetComponentType<SpotLightComponent>()
//     };
// }

// void SpotLightController::SetCameraId(EntityId id)
// {
//     m_cameraId = id;
// }

// void SpotLightController::Update(Window &window, Scene& scene, bool debug)
// {
//     auto sceneEntities = scene.GetEntities();
//     auto& camera = GetComponent<CameraComponent>(m_cameraId);

//     AssetManager& assetManager = AssetManager::GetInstance();
//     auto program = assetManager.GetShaderProgram("Material");
//     program->Use();

//     int i = 0;
//     for (auto const& id : m_entities)
//     {
//         // TODO: find a better way of limiting the update to the intersection of system and scene entities
//         if (sceneEntities.find(id) == sceneEntities.end()) continue;

//         auto& transform = GetComponent<TransformComponent>(id);
//         auto& spotLight = GetComponent<SpotLightComponent>(id);

//         // For demo purposes while there's only one spot light defined.
//         // This kind of thing should be handled via scene graph traversal
//         transform.position = camera.position;
//         spotLight.direction = camera.front;

//         auto key = "spotLights[" + std::to_string(i) + "].";
//         program->SetUniform3f(key + "position", transform.position);
//         program->SetUniform3f(key + "ambient", spotLight.ambient);
//         program->SetUniform3f(key + "diffuse", spotLight.diffuse);
//         program->SetUniform3f(key + "specular", spotLight.specular);
//         program->SetUniform3f(key + "direction", spotLight.direction);
//         program->SetUniformFloat(key + "innerEdge", spotLight.innerEdge);
//         program->SetUniformFloat(key + "outerEdge", spotLight.outerEdge);
//         program->SetUniformFloat(key + "constant", spotLight.constant);
//         program->SetUniformFloat(key + "linear", spotLight.linear);
//         program->SetUniformFloat(key + "quadratic", spotLight.quadratic);

//         i++;
//     }

//     program->SetUniformInt("spotLightCount", i);
// }
