#pragma once

#include <glm/glm.hpp>

namespace Iris
{
    struct GLVertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };
}