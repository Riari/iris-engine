#pragma once

#include <memory>

#include "GL/Shader/ShaderProgram.hpp"
#include "System.hpp"

namespace Iris
{
    // Temporary system
    class LightingDemo : public System
    {
    public:
        static std::list<ComponentType> GetComponentTypes();

        void Update(Window&, Scene&) override;
    };
}