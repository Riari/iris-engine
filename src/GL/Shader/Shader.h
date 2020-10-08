#pragma once

#include <iostream>
#include <glad\glad.h>

class Shader
{
public:
    Shader(GLenum type, const std::string &name, const std::string &suffix);

    ~Shader();

    [[nodiscard]] unsigned int GetID() const;

    void Compile() const;

private:
    const unsigned int m_id;
    const std::string m_name;
    const std::string m_path = "resources\\shaders\\";
    const std::string m_extension = ".glsl";

    [[nodiscard]] std::string LoadSource() const;
};
