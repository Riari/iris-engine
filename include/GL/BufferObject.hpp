#pragma once

#include <memory>

#include "Object.hpp"

namespace Iris
{
    class BufferObject : protected Object
    {
    public:
        explicit BufferObject(unsigned int target);

        ~BufferObject();

        void Bind() const;

        void SetData(unsigned int size, const void *data, unsigned int usage) const;

        void Unbind() const;

    private:
        unsigned int m_target;
    };
}
