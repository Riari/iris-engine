#include "Pipeline.hpp"

using namespace Iris;

Pipeline::Pipeline(flecs::world &world) : m_pipeline(world.pipeline("Default")),
                                          m_beginFrame(Phase(world, m_pipeline, flecs::PreFrame)),
                                          m_pollEvents(Phase(world, m_pipeline, world.entity())),
                                          m_updateState(Phase(world, m_pipeline, world.entity())),
                                          m_renderWorld(Phase(world, m_pipeline, world.entity())),
                                          m_postRenderWorld(Phase(world, m_pipeline, world.entity())),
                                          m_renderUI(Phase(world, m_pipeline, world.entity())),
                                          m_endFrame(Phase(world, m_pipeline, flecs::PostFrame))
{
}
