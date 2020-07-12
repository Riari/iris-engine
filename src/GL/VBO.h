#pragma once

#include "BufferObject.h"

class VBO : public BufferObject {
public:
    VBO();

    static void SetVertexAttribute(unsigned int location, unsigned int size);
};
