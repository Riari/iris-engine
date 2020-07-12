#include <glad/glad.h>
#include "VAO.h"

VAO::VAO() {
    glGenBuffers(1, &m_vao);
}

void VAO::Bind() const {
    glBindVertexArray(m_vao);
}

void VAO::Release() const {
    glDeleteVertexArrays(1, &m_vao);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

