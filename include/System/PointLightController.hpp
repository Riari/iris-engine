#pragma once

#include <memory>

#include "GL/Shader/ShaderProgram.hpp"
#include "System.hpp"

namespace Iris
{
    class PointLightController : public System
    {
    public:
        static std::list<ComponentType> GetComponentTypes();

        void Update(Window&, Scene&) override;
    };
}