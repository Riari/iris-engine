#include "VBO.h"

VBO::VBO() : BufferObject(GL_ARRAY_BUFFER) {}

void VBO::SetVertexAttribute(unsigned int location, unsigned int size) {
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)0);
    glEnableVertexAttribArray(location);
}
