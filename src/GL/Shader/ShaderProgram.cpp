#include <memory>
#include <glad\glad.h>
#include "ShaderProgram.h"
#include "VertexShaderSource.h"
#include "FragmentShaderSource.h"
#include "../../Exception/Exception.h"

ShaderProgram::ShaderProgram(std::string name) :
    m_name(std::move(name)),
    m_vertexShader(glCreateShader(GL_VERTEX_SHADER)),
    m_vertexShaderSource(new VertexShaderSource(m_name)),
    m_fragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
    m_fragmentShaderSource(new FragmentShaderSource(m_name)) {
    Compile();
}

void ShaderProgram::Compile() const {
    glShaderSource(m_vertexShader, 1, reinterpret_cast<const GLchar *const *>(m_vertexShaderSource->GetSource()), NULL);
    glCompileShader(m_vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
        throw Exception("Vertex shader compilation failed");
    }
}