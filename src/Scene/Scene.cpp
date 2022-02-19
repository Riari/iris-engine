#include "Scene.hpp"

using namespace Iris;

Scene::Scene(int id) : m_id(id) {}

void Scene::SetClearColor(glm::vec4 color)
{
    m_clearColor = color;
}

glm::vec4 Scene::GetClearColor()
{
    return m_clearColor;
}

void Scene::AddEntity(EntityId entityId)
{
    m_entityIds.insert(entityId);
}

std::set<EntityId> Scene::GetEntities()
{
    return m_entityIds;
}

void Scene::RemoveEntity(EntityId entityId)
{
    m_entityIds.erase(entityId);
}
