#pragma once

#include <memory>
#include "../Asset/Image.h"

class Texture {
public:
    explicit Texture(std::shared_ptr<Image> image);

    void Bind() const;
    void Generate() const;

    static void GenerateMipmap();
    static void SetWrapMethod(GLint param);
    static void SetFilterMethod(GLint param);
private:
    unsigned int m_texture{};
    std::shared_ptr<Image> m_image;
};