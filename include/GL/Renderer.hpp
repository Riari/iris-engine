#pragma once

#include <glm/glm.hpp>

namespace Iris
{
    class Renderer
    {
    public:
        static void EnableCapability(unsigned int capability);
        static void SetViewport(int w, int h);
        static void Clear(glm::vec4 color = glm::vec4(0.1f, 0.1f, 0.14f, 1.0f));
    };
}