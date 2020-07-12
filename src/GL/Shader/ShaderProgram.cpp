#include <memory>
#include <glad\glad.h>
#include <spdlog\spdlog.h>
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "../../Exception/Exception.h"

ShaderProgram::ShaderProgram(std::string name) :
    m_name(std::move(name)),
    m_program(glCreateProgram()),
    m_vertexShader(new VertexShader(m_name)),
    m_fragmentShader(new FragmentShader(m_name)) {}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_program);
}

void ShaderProgram::Compile() const {
    m_vertexShader->Compile();
    m_fragmentShader->Compile();
}

void ShaderProgram::Link() const {
    glAttachShader(m_program, m_vertexShader->GetID());
    glAttachShader(m_program, m_fragmentShader->GetID());
    glLinkProgram(m_program);

    GLint success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

        std::string info;
        info.resize(static_cast<std::string::size_type>(maxLength - 1));
        glGetProgramInfoLog(m_program, 512, NULL, info.data());
        throw Exception("Program linking failed: " + info);
    }

    spdlog::info("Shader program " + m_name + " linked");
}

void ShaderProgram::Release() {
    delete m_vertexShader;
    delete m_fragmentShader;
}

void ShaderProgram::Use() const {
    glUseProgram(m_program);
}
