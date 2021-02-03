#pragma once

#include <memory>

namespace Iris
{
    class BufferObject
    {
    public:
        explicit BufferObject(unsigned int target);

        ~BufferObject();

        void Bind() const;

        void SetData(unsigned int size, const void *data, unsigned int usage) const;

        void Unbind() const;

    private:
        unsigned int m_vbo{};
        unsigned int m_target;
        const unsigned int *m_buffer{};
    };
}
