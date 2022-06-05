#pragma once

#include <memory>
#include "GL/Texture.hpp"

namespace Iris::GL
{
    enum TextureDataType
    {
        Diffuse,
        Specular,
        Emission,
        Normal,
        Height,
    };

    struct TextureData
    {
        std::shared_ptr<GL::Texture> texture;
        TextureDataType type;
        const char* path;
    };
}
