#pragma once

#include <glm/glm.hpp>

#include "GL/Texture.hpp"

namespace Iris
{
    struct Material
    {
        std::shared_ptr<Texture> pDiffuseMap;
        std::shared_ptr<Texture> pSpecularMap;
        std::shared_ptr<Texture> pEmissionMap;
        float shininess;
    };
}