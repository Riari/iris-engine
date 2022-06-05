#pragma once

#include <flecs.h>

namespace Iris
{
    class Phase
    {
    public:
        flecs::world &m_world;
        flecs::entity_t m_phase;

        Phase(flecs::world &world, flecs::pipeline pipeline, flecs::entity_t phase);

        template <typename... Types>
        flecs::system_builder<Types...> Add() const
        {
            return m_world.system<Types...>().kind(m_phase);
        }
    };
};
