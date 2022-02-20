#pragma once

#include <memory>

#include "../Texture.hpp"

namespace Iris
{
    enum GLTextureType
    {
        Diffuse,
        Specular,
        Emission,
        Normal,
        Height,
    };

    struct GLTexture
    {
        std::shared_ptr<Texture> texture;
        GLTextureType type;
        const char* path;
    };
}