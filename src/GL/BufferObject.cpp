#include <glad/glad.h>

#include "GL/BufferObject.hpp"

using namespace OGL;

BufferObject::BufferObject(unsigned int target) : m_target(target)
{
    glGenBuffers(1, &m_vbo);
}

BufferObject::~BufferObject()
{
    glDeleteBuffers(1, &m_vbo);
}

void BufferObject::Bind() const
{
    glBindBuffer(m_target, m_vbo);
}

void BufferObject::SetData(unsigned int size, const void *data, const unsigned int usage) const
{
    glBufferData(m_target, size, data, usage);
}

void BufferObject::Unbind() const
{
    glBindBuffer(m_target, 0);
}
