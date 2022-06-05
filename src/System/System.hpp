#pragma once

#include <flecs.h>

namespace Iris
{
    template <typename... Components>
    class System
    {
    public:
        System(flecs::world &world, flecs::entity &phase) : m_system(world.system<Components...>().kind(phase))
        {
            Init(m_system);
        }

    private:
        flecs::system::entity m_system;

        virtual void Init(flecs::system::entity) = 0;
    };
}
