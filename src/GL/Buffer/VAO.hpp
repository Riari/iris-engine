#pragma once

#include "../Object.hpp"

namespace Iris
{
    class VAO : protected Object
    {
    public:
        VAO();
        ~VAO();

        void Bind() const;
        static void Unbind();
        static void SetAttrPointer(unsigned int location, unsigned int size, unsigned int stride,
                                       const void *pointer = (void *) nullptr);
    };
}
