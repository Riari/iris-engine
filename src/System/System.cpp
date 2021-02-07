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
