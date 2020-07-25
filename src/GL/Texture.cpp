#include <glad/glad.h>

#include <utility>
#include "Texture.h"

Texture::Texture(std::shared_ptr<Image> image) : m_image(std::move(image)) {
    glGenTextures(1, &m_texture);
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::Generate() const {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *m_image->GetData(), *m_image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image->GetData());
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


