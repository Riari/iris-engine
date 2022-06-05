#pragma once

#include <glad/glad.h>

namespace Iris::GL
{
    class Object
    {
    public:
        [[nodiscard]] GLuint GetID() const;
    protected:
        GLuint m_id;
    };
}
