#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>

#include "Entity/Event/AddComponentEvent.hpp"
#include "Entity/Event/DestroyEntityEvent.hpp"
#include "Entity/Event/RemoveComponentEvent.hpp"
#include "Component.hpp"
#include "ComponentStore.hpp"
#include "Event/EventBus.hpp"
#include "Event/EventHandler.hpp"

namespace Iris
{
    class ComponentManager : public EventHandler<DestroyEntityEvent>
    {
    public:
        ComponentManager(ComponentManager const&) = delete;
        void operator=(ComponentManager const&) = delete;

        static ComponentManager& GetInstance()
        {
            static ComponentManager instance;
            return instance;
        }

        template<typename T>
        void RegisterComponentType()
        {
            const char* typeName = typeid(T).name();

            assert(m_types.find(typeName) == m_types.end() && "Registering component type more than once.");

            m_types.insert({typeName, m_nextType});
            m_stores.insert({typeName, std::make_shared<ComponentStore<T>>()});

            ++m_nextType;
        }

        template<typename T>
        ComponentType GetComponentType()
        {
            const char* typeName = typeid(T).name();

            assert(m_types.find(typeName) != m_types.end() && "Component not registered before use.");

            return m_types[typeName];
        }

        template<typename T>
        void AddComponent(EntityId id, T component)
        {
            GetComponentStore<T>()->Insert(id, component);

            EventBus::Dispatch<AddComponentEvent>(AddComponentEvent(id, GetComponentType<T>()));
        }

        template<typename T>
        void RemoveComponent(EntityId id)
        {
            GetComponentStore<T>()->Remove(id);

            EventBus::Dispatch<RemoveComponentEvent>(RemoveComponentEvent(id, GetComponentType<T>()));
        }

        template<typename T>
        T& GetComponent(EntityId id)
        {
            return GetComponentStore<T>()->Get(id);
        }

        bool Handle(const DestroyEntityEvent &event) override
        {
            for (auto const& [_, component] : m_stores)
            {
                component->EntityDestroyed(event.GetEntityId());
            }

            return false;
        }

    private:
        ComponentManager() = default;

        std::unordered_map<const char*, ComponentType> m_types{};
        std::unordered_map<const char*, std::shared_ptr<IComponentStore>> m_stores{};
        ComponentType m_nextType{};

        template<typename T>
        std::shared_ptr<ComponentStore<T>> GetComponentStore()
        {
            const char* typeName = typeid(T).name();

            assert(m_types.find(typeName) != m_types.end() && "Component not registered before use.");

            return std::static_pointer_cast<ComponentStore<T>>(m_stores[typeName]);
        }
    };
}