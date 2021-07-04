#pragma once

#include <glm/glm.hpp>

namespace Iris
{
    struct SpotLight
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        glm::vec3 direction;
        float innerEdge;
        float outerEdge;
        float constant;
        float linear;
        float quadratic;
    };
}