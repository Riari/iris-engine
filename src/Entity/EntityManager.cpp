#include <cassert>

#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"
#include "Entity/Event/DestroyEntityEvent.hpp"
#include "Entity/Event/EntitySignatureChangeEvent.hpp"

using namespace Iris;

EntityManager& EntityManager::GetInstance()
{
    static EntityManager instance;
    return instance;
}

EntityManager::EntityManager()
{
    for (EntityId id = 0; id < MAX_ENTITIES; ++id) m_entityIds.push(id);
}

EntityId EntityManager::CreateEntity()
{
    assert(m_livingEntityCount < MAX_ENTITIES && "Maximum entity count exceeded");

    EntityId id = m_entityIds.front();
    m_entityIds.pop();
    ++m_livingEntityCount;

    return id;
}

void EntityManager::DestroyEntity(EntityId id)
{
    assert(id < MAX_ENTITIES && "Entity ID out of range.");

    m_entitySignatures[id].reset();

    m_entityIds.push(id);
    --m_livingEntityCount;

    EventBus::Dispatch<DestroyEntityEvent>(DestroyEntityEvent(id));
}

void EntityManager::SetSignature(EntityId id, Signature signature)
{
    assert(id < MAX_ENTITIES && "Entity ID out of range.");

    m_entitySignatures[id] = signature;
}

Signature EntityManager::GetSignature(EntityId id)
{
    assert(id < MAX_ENTITIES && "Entity ID out of range.");

    return m_entitySignatures[id];
}

bool EntityManager::Handle(const AddComponentEvent &event)
{
    auto signature = GetSignature(event.GetEntityId());
    signature.set(event.GetComponentType(), true);
    SetSignature(event.GetEntityId(), signature);

    EventBus::Dispatch<EntitySignatureChangeEvent>(EntitySignatureChangeEvent(event.GetEntityId(), signature));

    return true;
}

bool EntityManager::Handle(const RemoveComponentEvent &event)
{
    auto signature = GetSignature(event.GetEntityId());
    signature.set(event.GetComponentType(), false);
    SetSignature(event.GetEntityId(), signature);

    EventBus::Dispatch<EntitySignatureChangeEvent>(EntitySignatureChangeEvent(event.GetEntityId(), signature));

    return true;
}
