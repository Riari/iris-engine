#pragma once

#include <list>
#include "Entity/ComponentManager.hpp"
#include "Entity/Entity.hpp"
#include "Scene/Scene.hpp"
#include "Window/Window.hpp"

namespace Iris
{
    class System
    {
    public:
        void AddEntity(EntityId);
        void RemoveEntity(EntityId);

        static std::list<ComponentType> GetComponentTypes();

        std::set<EntityId> GetEntities();

        virtual void Update(Window&, bool debug);
        virtual void Update(Window&, Scene&, bool debug);

    protected:
        std::set<EntityId> m_entities;

        template<typename T>
        static ComponentType GetComponentType()
        {
            return ComponentManager::GetInstance().GetComponentType<T>();
        }

        template<typename T>
        static T& GetComponent(EntityId id)
        {
            return ComponentManager::GetInstance().GetComponent<T>(id);
        }
    };
}