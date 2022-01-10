#pragma once

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
        unsigned int id;
        GLTextureType type;
        const char* path;
    };
}