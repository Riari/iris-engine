#include <glad/glad.h>

#include "GL/VBO.hpp"

using namespace Iris;

VBO::VBO() : BufferObject(GL_ARRAY_BUFFER) {}

void VBO::SetVertexAttribute(unsigned int location, unsigned int size, unsigned int stride, const void *pointer)
{
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(location);
}
