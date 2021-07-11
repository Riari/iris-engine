#pragma once

#include <cassert>
#include <list>
#include <memory>
#include <unordered_map>

#include "Entity/Entity.hpp"
#include "Entity/Event/DestroyEntityEvent.hpp"
#include "Entity/Event/EntitySignatureChangeEvent.hpp"
#include "Event/EventHandler.hpp"
#include "System.hpp"

namespace Iris
{
    class SystemManager :
            public EventHandler<DestroyEntityEvent>,
            public EventHandler<EntitySignatureChangeEvent>
    {
    public:
        SystemManager(SystemManager const&) = delete;
        void operator=(SystemManager const&) = delete;

        static SystemManager& GetInstance()
        {
            static SystemManager instance;
            return instance;
        }

        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            const char* typeName = typeid(T).name();

            assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

            auto system = std::make_shared<T>();
            m_systems.insert({typeName, system});

            Signature signature;
            for (auto const& type : T::GetComponentTypes())
            {
                signature.set(type);
            }

            SetSignature<T>(signature);

            return system;
        }

        std::unordered_map<const char*, std::shared_ptr<System>> GetSystems()
        {
            return m_systems;
        }

        template<typename T>
        std::shared_ptr<System> GetSystem()
        {
            const char* typeName = typeid(T).name();

            assert(m_systems.find(typeName) != m_systems.end() && "System retrieved before registered.");

            return m_systems.find(typeName)->second;
        }

        template<typename T>
        void SetSignature(Signature signature)
        {
            const char* typeName = typeid(T).name();

            assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

            m_signatures.insert({typeName, signature});
        }

        bool Handle(const DestroyEntityEvent &event) override
        {
            for (auto const& [_, system] : m_systems)
            {
                system->RemoveEntity(event.GetEntityId());
            }

            return false;
        }

        bool Handle(const EntitySignatureChangeEvent &event) override
        {
            for (auto const& [type, system] : m_systems)
            {
                if ((event.GetSignature() & m_signatures[type]) == m_signatures[type]) system->AddEntity(event.GetEntityId());
                else system->RemoveEntity(event.GetEntityId());
            }

            return true;
        }

    private:
        SystemManager() = default;

        std::unordered_map<const char*, Signature> m_signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
    };
}