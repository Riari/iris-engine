#include "Entity/Event/AddComponentEvent.hpp"

using namespace Iris;

AddComponentEvent::AddComponentEvent(EntityId entityId, ComponentType componentType) :
    m_entityId(entityId), m_componentType(componentType) {}

EntityId AddComponentEvent::GetEntityId() const
{
    return m_entityId;
}

ComponentType AddComponentEvent::GetComponentType() const
{
    return m_componentType;
}
