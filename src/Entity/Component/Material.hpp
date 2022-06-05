#pragma once

#include <glm/glm.hpp>
#include "GL/Texture.hpp"

namespace Iris
{
    struct Material
    {
        std::shared_ptr<GL::Texture> pDiffuseMap;
        std::shared_ptr<GL::Texture> pSpecularMap;
        std::shared_ptr<GL::Texture> pEmissionMap;
        float shininess;
    };
}
