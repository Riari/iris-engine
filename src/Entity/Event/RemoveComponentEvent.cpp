#include "Entity/Event/RemoveComponentEvent.hpp"

using namespace Iris;

RemoveComponentEvent::RemoveComponentEvent(EntityId entityId, ComponentType componentType) :
        m_entityId(entityId), m_componentType(componentType) {}

EntityId RemoveComponentEvent::GetEntityId() const
{
    return m_entityId;
}

ComponentType RemoveComponentEvent::GetComponentType() const
{
    return m_componentType;
}
