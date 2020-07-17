#pragma once

#include <string>
#include <memory>
#include "Shader.h"

class ShaderProgram {
public:
    explicit ShaderProgram(std::string name);
    ~ShaderProgram();

    void Compile() const;
    void Link() const;
    void DeleteShaders();
    void Use() const;
    [[nodiscard]] int GetUniformLocation(const std::string& name) const;
    void SetUniform4f(const std::string& uniform, std::vector<float> values) const;
private:
    const std::string m_name;
    unsigned int m_program;
    Shader* m_vertexShader;
    Shader* m_fragmentShader;
};