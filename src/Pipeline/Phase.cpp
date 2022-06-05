#include "Phase.hpp"

using namespace Iris;

Phase::Phase(flecs::world &world, flecs::pipeline pipeline, flecs::entity_t phase) : m_world(world), m_phase(phase)
{
    pipeline.add(m_phase);
}
