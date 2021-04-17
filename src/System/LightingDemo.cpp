#include "Entity/Component/PointLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "Scene/Scene.hpp"
#include "System/LightingDemo.hpp"

using namespace Iris;

std::list<ComponentType> LightingDemo::GetComponentTypes()
{
    return {
        GetComponentType<Transform>(),
        GetComponentType<PointLight>()
    };
}

void LightingDemo::Update(Window &window, Scene& scene)
{
    auto sceneEntities = scene.GetEntities();

    for (auto const& id : m_entities)
    {
        // TODO: find a better way of limiting the update to the intersection of system and scene entities
        if (sceneEntities.find(id) == sceneEntities.end()) continue;

        auto& transform = GetComponent<Transform>(id);
        transform.position = glm::vec3(1.0f + sin(window.GetLastLoopTime()) * 2.0f, sin(window.GetLastLoopTime() / 2.0f) * 1.0f, 0.0f);
    }
}
