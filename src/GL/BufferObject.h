#pragma once

#include <glad\glad.h>
#include <memory>

class BufferObject {
public:
    explicit BufferObject(GLenum target);
    void Bind() const;
    void SetData(const void *data, GLenum usage) const;
private:
    unsigned int m_vbo{};
    GLenum m_target;
    const unsigned int *m_buffer{};
    const void *m_data{};
};
