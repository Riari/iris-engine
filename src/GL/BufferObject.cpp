#include "BufferObject.h"

BufferObject::BufferObject(GLenum target) : m_target(target) {
    glGenBuffers(1, &m_vbo);
}

void BufferObject::Bind() const {
    glBindBuffer(m_target, m_vbo);
}

void BufferObject::SetData(const void *data, const GLenum usage) const {
    glBufferData(m_target, sizeof(data), data, usage);
}