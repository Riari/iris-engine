#include "System/System.hpp"

using namespace Iris;

void System::AddEntity(EntityId id)
{
    m_entities.insert(id);
}

void System::RemoveEntity(EntityId id)
{
    m_entities.erase(id);
}

std::list<ComponentType> System::GetComponentTypes()
{
    return {};
}

std::set<EntityId> System::GetEntities()
{
    return m_entities;
}

void System::Update(Window& window, bool debug)
{
    // noop
}

void System::Update(Window& window, Scene& scene, bool debug)
{
    // noop
}
