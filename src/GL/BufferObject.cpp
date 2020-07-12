#include "BufferObject.h"

BufferObject::BufferObject(GLenum target) : m_target(target) {
    glGenBuffers(1, &m_vbo);
}

void BufferObject::Bind() const {
    glBindBuffer(m_target, m_vbo);
}

void BufferObject::SetData(const void *data, unsigned int size, const GLenum usage) const {
    glBufferData(m_target, size, data, usage);
}

void BufferObject::Release() const {
    glDeleteBuffers(1, &m_vbo);
}

void BufferObject::Unbind() const {
    glBindBuffer(m_target, 0);
}
