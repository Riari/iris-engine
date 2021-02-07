#include "Entity/Event/DestroyEntityEvent.hpp"

using namespace Iris;

DestroyEntityEvent::DestroyEntityEvent(EntityId entityId) : m_entityId(entityId) {}

EntityId DestroyEntityEvent::GetEntityId() const
{
    return m_entityId;
}
