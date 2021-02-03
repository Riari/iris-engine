#pragma once

namespace Iris
{
    class VAO
    {
    public:
        VAO();

        ~VAO();

        void Bind() const;

        static void Unbind();

    private:
        unsigned int m_vao{};
    };
}
