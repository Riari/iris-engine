#include <glad/glad.h>

#include "GL/VAO.hpp"

using namespace Iris;

VAO::VAO() : Object()
{
    glGenVertexArrays(1, &m_id);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_id);
}

void VAO::Bind() const
{
    glBindVertexArray(m_id);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}
