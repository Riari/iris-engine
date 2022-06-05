#include <memory>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "GL/Shader/ShaderProgram.hpp"
#include "Exception/Exception.hpp"

using namespace Iris::GL;

ShaderProgram::ShaderProgram(std::string name, std::shared_ptr<spdlog::logger> logger) :
    m_name(std::move(name)),
    m_program(glCreateProgram()),
    m_vertexShader(new Shader(GL_VERTEX_SHADER, m_name, ".vert", logger)),
    m_fragmentShader(new Shader(GL_FRAGMENT_SHADER, m_name, ".frag", logger)),
    m_logger(std::move(logger))
{}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_program);
}

void ShaderProgram::Build()
{
    Compile();
    Link();
    DeleteShaders();
}

void ShaderProgram::Use() const
{
    glUseProgram(m_program);
}

int ShaderProgram::GetUniformLocation(const std::string &name) const
{
    return glGetUniformLocation(m_program, name.c_str());
}

void ShaderProgram::SetUniformBool(const std::string &name, bool value) const
{
    SetUniformInt(name, (int) value);
}

void ShaderProgram::SetUniformInt(const std::string &name, int value) const
{
    glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniformFloat(const std::string &name, float value) const
{
    glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform3f(const std::string &name, glm::vec3 values) const
{
    glUniform3f(GetUniformLocation(name), values[0], values[1], values[2]);
}

void ShaderProgram::SetUniform4f(const std::string &name, glm::vec4 values) const
{
    glUniform4f(GetUniformLocation(name), values[0], values[1], values[2], values[3]);
}

void ShaderProgram::SetUniformMatrix4fv(const std::string &name, const float *value_ptr) const
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr);
}

void ShaderProgram::Compile() const
{
    m_vertexShader->Compile();
    m_fragmentShader->Compile();
}

void ShaderProgram::Link() const
{
    glAttachShader(m_program, m_vertexShader->GetID());
    glAttachShader(m_program, m_fragmentShader->GetID());
    glLinkProgram(m_program);

    GLint success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

        std::string info;
        info.resize(static_cast<std::string::size_type>(maxLength - 1));
        glGetProgramInfoLog(m_program, 512, NULL, info.data());
        throw Exception(fmt::format("Program linking failed: {0}", info));
    }

    m_logger->info(fmt::format("ShaderProgram {0} linked", m_name));
}

void ShaderProgram::DeleteShaders()
{
    delete m_vertexShader;
    delete m_fragmentShader;
}
