#pragma once

#include <flecs.h>
#include "System.hpp"
#include "Entity/Component/Camera.hpp"

namespace Iris
{
    class CameraController : public System<Camera>
    {
    private:
        void Init(flecs::system::entity);
    };
};
