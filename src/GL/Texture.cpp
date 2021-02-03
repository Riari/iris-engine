#include <utility>

#include <fmt/core.h>
#include <glad/glad.h>

#include "Asset/Image.hpp"
#include "GL/Texture.hpp"
#include "Exception/Exception.hpp"

using namespace Iris;

Texture::Texture(std::shared_ptr<Image> image) : m_image(std::move(image))
{
    glGenTextures(1, &m_texture);
}

void Texture::Bind(GLenum unit) const
{
    glActiveTexture(unit);
    Bind();
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::Define(bool withMipmap) const
{
    GLint format;

    switch (m_image->GetChannels())
    {
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            throw Exception(fmt::format("Unexpected channel count in image data: {0} ({1} channels)",
                                        m_image->GetPath(), std::to_string(m_image->GetChannels())));
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_image->GetWidth(), m_image->GetHeight(), 0, format, GL_UNSIGNED_BYTE,
                 m_image->GetData());

    if (withMipmap) GenerateMipmap();
}

void Texture::GenerateMipmap()
{
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::SetWrapMethod(GLint param)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
}

void Texture::SetFilterMethod(GLint param)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
}
