#pragma once

#include <memory>

#include "Asset/Image.hpp"
#include "GL/Object.hpp"

namespace Iris
{
    class Texture : protected Object
    {
    public:
        explicit Texture(std::shared_ptr<Image> image);

        void Bind(GLenum unit) const;

        void Bind() const;

        void Define(bool withMipmap = true) const;

        static void GenerateMipmap();

        static void SetWrapMethod(GLint param);

        static void SetFilterMethod(GLint param);

    private:
        std::shared_ptr<Image> m_image;
    };
}
