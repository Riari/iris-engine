#pragma once

#include <glm/glm.hpp>

namespace Iris
{
    struct PointLightComponent
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float constant;
        float linear;
        float quadratic;
    };
}