#pragma once

#include <glm/glm.hpp>

namespace Iris
{
    struct PointLight
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float constant;
        float linear;
        float quadratic;
    };
}