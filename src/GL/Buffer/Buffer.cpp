#include <glad/glad.h>
#include "GL/Buffer/Buffer.hpp"

using namespace Iris::GL;

Buffer::Buffer(unsigned int target) : Object(), m_target(target)
{
    glGenBuffers(1, &m_id);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_id);
}

void Buffer::Bind() const
{
    glBindBuffer(m_target, m_id);
}

void Buffer::SetData(unsigned int size, const void *data, const unsigned int usage) const
{
    glBufferData(m_target, size, data, usage);
}

void Buffer::Unbind() const
{
    glBindBuffer(m_target, 0);
}
