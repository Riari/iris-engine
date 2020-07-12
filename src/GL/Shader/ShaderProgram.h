#pragma once

#include <string>
#include <memory>
#include "Shader.h"

class ShaderProgram {
public:
    explicit ShaderProgram(std::string name);

    void Compile() const;
    void Link() const;
    void CleanUp();
    void Use() const;
private:
    const std::string m_name;
    unsigned int m_program;
    Shader* m_vertexShader;
    Shader* m_fragmentShader;
};