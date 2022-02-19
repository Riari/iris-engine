#include <fstream>
#include <iostream>
#include <utility>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "Exception/Exception.hpp"
#include "Shader.hpp"

using namespace Iris;

Shader::Shader(unsigned int type, const std::string &name, const std::string &suffix,
               std::shared_ptr<spdlog::logger> logger) :
        Object(),
        m_name(name + suffix),
        m_logger(std::move(logger))
{
    m_id = glCreateShader(type);
}

Shader::~Shader()
{
    glDeleteShader(m_id);
}

GLuint Shader::GetID() const
{
    return m_id;
}

void Shader::Compile() const
{
    std::string source = LoadSource();
    GLchar const *shader_source = source.c_str();
    GLint const shader_length = source.size();
    glShaderSource(m_id, 1, &shader_source, &shader_length);
    glCompileShader(m_id);

    GLint success;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

        std::string info;
        info.resize(static_cast<std::string::size_type>(maxLength - 1));
        glGetShaderInfoLog(m_id, maxLength, &maxLength, info.data());
        throw Exception(fmt::format("Shader compilation failed: {0}", info));
    }

    m_logger->info(fmt::format("Shader {0}{1} compiled", m_name, m_extension));
}

std::string Shader::LoadSource() const
{
    std::string source;
    std::string filepath = m_path + m_name + m_extension;
    std::ifstream fileStream(filepath.c_str(), std::ios::in);

    if (!fileStream.is_open()) throw Exception(fmt::format("Failed to open {0}", filepath));

    std::string line;
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        source.append(line + "\n");
    }

    fileStream.close();

    return source;
}
