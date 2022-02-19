#include "EntitySignatureChangeEvent.hpp"

using namespace Iris;

EntitySignatureChangeEvent::EntitySignatureChangeEvent(EntityId entityId, Signature signature) :
        m_entityId(entityId), m_signature(signature) {}

EntityId EntitySignatureChangeEvent::GetEntityId() const
{
    return m_entityId;
}

Signature EntitySignatureChangeEvent::GetSignature() const
{
    return m_signature;
}
