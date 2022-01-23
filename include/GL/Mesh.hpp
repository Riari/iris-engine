#pragma once

#include <vector>

#include "GLTexture.hpp"
#include "GLVertex.hpp"
#include "Shader/ShaderProgram.hpp"

namespace Iris
{
    class Mesh
    {
    public:
        Mesh(std::vector<GLVertex> vertices, std::vector<unsigned int> indices, std::vector<GLTexture> textures);
        void Draw(const std::shared_ptr<ShaderProgram>& program);

    private:
        // MeshComponent data
        std::vector<GLVertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<GLTexture> m_textures;

        // Render data
        unsigned int m_vao, m_vbo, m_ebo;

        void Init();
    };
}