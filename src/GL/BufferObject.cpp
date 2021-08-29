#include <glad/glad.h>

#include "GL/BufferObject.hpp"

using namespace Iris;

BufferObject::BufferObject(unsigned int target) : Object(), m_target(target)
{
    glGenBuffers(1, &m_id);
}

BufferObject::~BufferObject()
{
    glDeleteBuffers(1, &m_id);
}

void BufferObject::Bind() const
{
    glBindBuffer(m_target, m_id);
}

void BufferObject::SetData(unsigned int size, const void *data, const unsigned int usage) const
{
    glBufferData(m_target, size, data, usage);
}

void BufferObject::Unbind() const
{
    glBindBuffer(m_target, 0);
}
