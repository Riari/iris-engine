#pragma once

#include <array>
#include <queue>
#include "Entity/Event/AddComponentEvent.hpp"
#include "Entity/Event/RemoveComponentEvent.hpp"
#include "Event/EventHandler.hpp"
#include "Entity.hpp"

namespace Iris
{
    class EntityManager :
            public EventHandler<AddComponentEvent>,
            public EventHandler<RemoveComponentEvent>
    {
    public:
        EntityManager(EntityManager const&) = delete;
        void operator=(EntityManager const&) = delete;

        static EntityManager& GetInstance();

        EntityId CreateEntity();
        void DestroyEntity(EntityId);
        void SetSignature(EntityId, Signature);
        Signature GetSignature(EntityId);

        bool Handle(const AddComponentEvent&) override;
        bool Handle(const RemoveComponentEvent&) override;

    private:
        EntityManager();

        std::queue<EntityId> m_entityIds{};
        std::array<Signature, MAX_ENTITIES> m_entitySignatures{};
        uint32_t m_livingEntityCount{};
    };
}