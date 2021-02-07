#pragma once

#include "Entity/Entity.hpp"
#include "Event/Event.hpp"

namespace Iris
{
    class DestroyEntityEvent : public Event
    {
    public:
        DestroyEntityEvent(EntityId);

        [[nodiscard]] EntityId GetEntityId() const;

    private:
        EntityId m_entityId;
    };
}