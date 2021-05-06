#pragma once

#include <glm/glm.hpp>

#include "GL/Texture.hpp"

namespace Iris
{
    struct Material
    {
        std::shared_ptr<Texture> diffuseTexture;
        glm::vec3 specular;
        float shininess;
    };
}