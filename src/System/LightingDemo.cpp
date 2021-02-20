#include "Entity/Component/PointLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "System/LightingDemo.hpp"

using namespace Iris;

std::list<ComponentType> LightingDemo::GetComponentTypes()
{
    return {
        GetComponentType<Transform>(),
        GetComponentType<PointLight>()
    };
}

void LightingDemo::Update(Window &window)
{
    for (auto const& id : m_entities)
    {
        auto& transform = GetComponent<Transform>(id);
        transform.position = glm::vec3(1.0f + sin(window.GetLastLoopTime()) * 2.0f, sin(window.GetLastLoopTime() / 2.0f) * 1.0f, 0.0f);
    }
}
