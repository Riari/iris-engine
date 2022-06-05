#pragma once

#include <flecs.h>
#include "Phase.hpp"

namespace Iris
{
    struct Pipeline
    {
        flecs::pipeline m_pipeline;

        Phase m_beginFrame;
        Phase m_pollEvents;
        Phase m_updateState;
        Phase m_renderWorld;
        Phase m_postRenderWorld;
        Phase m_renderUI;
        Phase m_endFrame;

        explicit Pipeline(flecs::world &world);
    };
}
