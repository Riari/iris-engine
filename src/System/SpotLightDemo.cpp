#include "Entity/Component/Camera.hpp"
#include "Entity/Component/SpotLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "Scene/Scene.hpp"
#include "System/SpotLightDemo.hpp"

using namespace Iris;

std::list<ComponentType> SpotLightDemo::GetComponentTypes()
{
    return {
            GetComponentType<Transform>(),
            GetComponentType<SpotLight>()
    };
}

void SpotLightDemo::SetCameraId(EntityId id)
{
    m_cameraId = id;
}

void SpotLightDemo::Update(Window &window, Scene& scene)
{
    auto sceneEntities = scene.GetEntities();
    auto& camera = GetComponent<Camera>(m_cameraId);

    for (auto const& id : m_entities)
    {
        // TODO: find a better way of limiting the update to the intersection of system and scene entities
        if (sceneEntities.find(id) == sceneEntities.end()) continue;

        auto& transform = GetComponent<Transform>(id);
        transform.position = camera.position;

        auto& spotLight = GetComponent<SpotLight>(id);
        spotLight.direction = camera.front;
    }
}
