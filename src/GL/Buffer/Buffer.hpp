#pragma once

#include <memory>
#include "GL/Object.hpp"

namespace Iris::GL
{
    class Buffer : protected GL::Object
    {
    public:
        explicit Buffer(unsigned int target);
        ~Buffer();

        void Bind() const;
        void SetData(unsigned int size, const void *data, unsigned int usage) const;
        void Unbind() const;

    private:
        unsigned int m_target;
    };
}
