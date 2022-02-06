#pragma once

#include <vector>

#include "GLTexture.hpp"
#include "GLVertex.hpp"
#include "EBO.hpp"
#include "Shader/ShaderProgram.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

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

        // GL buffers
        std::unique_ptr<VAO> m_vao;
        std::unique_ptr<VBO> m_vbo;
        std::unique_ptr<EBO> m_ebo;

        void Init();
    };
}