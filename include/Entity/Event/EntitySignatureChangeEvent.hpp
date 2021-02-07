#pragma once

#include "Entity/Entity.hpp"
#include "Event/Event.hpp"

namespace Iris
{
    class EntitySignatureChangeEvent : public Event
    {
    public:
        EntitySignatureChangeEvent(EntityId entityId, Signature signature);

        [[nodiscard]] EntityId GetEntityId() const;
        [[nodiscard]] Signature GetSignature() const;

    private:
        EntityId m_entityId;
        Signature m_signature;
    };
}