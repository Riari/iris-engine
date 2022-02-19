#include <glad/glad.h>
#include "VAO.hpp"

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

void VAO::SetAttrPointer(unsigned int location, unsigned int size, unsigned int stride, const void *pointer)
{
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(location);
}
