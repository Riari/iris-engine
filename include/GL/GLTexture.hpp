#pragma once

namespace Iris
{
    enum GLTextureType
    {
        Diffuse,
        Specular,
        Emission
    };

    struct GLTexture
    {
        unsigned int id;
        TextureType type;
    };
}