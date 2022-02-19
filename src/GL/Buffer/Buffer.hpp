#pragma once

#include <memory>
#include "../Object.hpp"

namespace Iris
{
    class Buffer : protected Object
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
