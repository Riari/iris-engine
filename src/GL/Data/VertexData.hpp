#pragma once

#include <glm/glm.hpp>

namespace Iris::GL
{
    struct VertexData
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };
}
