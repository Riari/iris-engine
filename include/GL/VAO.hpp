#pragma once

#include "Object.hpp"

namespace Iris
{
    class VAO : protected Object
    {
    public:
        VAO();

        ~VAO();

        void Bind() const;

        static void Unbind();
    };
}
