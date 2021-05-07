#pragma once

#include <glm/glm.hpp>

#include "GL/Texture.hpp"

namespace Iris
{
    struct Material
    {
        std::shared_ptr<Texture> diffuseMap;
        std::shared_ptr<Texture> specularMap;
        std::shared_ptr<Texture> emissionMap;
        float shininess;
    };
}