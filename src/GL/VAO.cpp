#include <glad/glad.h>
#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &m_vao);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &m_vao);
}

void VAO::Bind() const {
    glBindVertexArray(m_vao);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

