#pragma once

#include <string>
#include <memory>
#include "ShaderSource.h"

class ShaderProgram {
public:
    explicit ShaderProgram(std::string name);
private:
    const std::string m_name;
    unsigned int m_vertexShader;
    ShaderSource* m_vertexShaderSource;
    unsigned int m_fragmentShader;
    ShaderSource* m_fragmentShaderSource;

    void Compile() const;
};