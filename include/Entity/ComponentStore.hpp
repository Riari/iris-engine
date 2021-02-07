#pragma once

#include <array>
#include <cassert>
#include <unordered_map>

#include "Entity.hpp"
#include "Component.hpp"

namespace Iris
{
    class IComponentStore
    {
    public:
        virtual ~IComponentStore() = default;
        virtual void EntityDestroyed(EntityId id) = 0;
    };

    template<typename T>
    class ComponentStore : public IComponentStore
    {
    public:
        void Insert(EntityId id, T component)
        {
            assert(m_entityToIndexMap.find(id) == m_entityToIndexMap.end() && "Component added to same entity more than once.");

            size_t newIndex = m_size;
            m_entityToIndexMap[id] = newIndex;
            m_indexToEntityMap[newIndex] = id;
            m_store[newIndex] = component;
            ++m_size;
        }

        void Remove(EntityId id)
        {
            assert(m_entityToIndexMap.find(id) != m_entityToIndexMap.end() && "Removing non-existent component.");

            size_t removedIndex = m_entityToIndexMap[id];
            size_t lastIndex = m_size - 1;
            m_store[removedIndex] = m_store[lastIndex];

            EntityId lastEntityId = m_indexToEntityMap[lastIndex];
            m_entityToIndexMap[lastEntityId] = removedIndex;
            m_indexToEntityMap[removedIndex] = lastIndex;

            m_entityToIndexMap.erase(id);
            m_indexToEntityMap.erase(lastIndex);

            --m_size;
        }

        T& Get(EntityId id)
        {
            assert(m_entityToIndexMap.find(id) != m_entityToIndexMap.end() && "Retrieving non-existent component.");

            return m_store[m_entityToIndexMap[id]];
        }

        void EntityDestroyed(EntityId id) override
        {
            if (m_entityToIndexMap.find(id) != m_entityToIndexMap.end()) Remove(id);
        }

    private:
        std::array<T, MAX_ENTITIES> m_store;
        std::unordered_map<EntityId, size_t> m_entityToIndexMap;
        std::unordered_map<size_t, EntityId> m_indexToEntityMap;
        size_t m_size;
    };
}
