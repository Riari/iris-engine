#include <glad/glad.h>

#include <utility>
#include "Texture.h"

Texture::Texture(std::shared_ptr<Image> image) : m_image(std::move(image)) {
    glGenTextures(1, &m_texture);
}

void Texture::Bind(GLenum unit) const {
    glActiveTexture(unit);
    Bind();
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::Define(bool withMipmap) const {
    Define(GL_RGB, true);
}

void Texture::Define(GLint format, bool withMipmap) const {
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_image->GetWidth(), m_image->GetHeight(), 0, format, GL_UNSIGNED_BYTE, m_image->GetData());

    if (withMipmap) GenerateMipmap();
}

void Texture::GenerateMipmap() {
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::SetWrapMethod(GLint param) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
}

void Texture::SetFilterMethod(GLint param) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
}


