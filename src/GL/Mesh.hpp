#pragma once

#include <vector>
#include "Buffer/EBO.hpp"
#include "Buffer/VAO.hpp"
#include "Buffer/VBO.hpp"
#include "Data/TextureData.hpp"
#include "Data/VertexData.hpp"
#include "Shader/ShaderProgram.hpp"

namespace Iris::GL
{
    class Mesh
    {
    public:
        Mesh(std::vector<VertexData> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures);
        void Draw(const std::shared_ptr<ShaderProgram>& program);

    private:
        // MeshComponent data
        std::vector<VertexData> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<TextureData> m_textures;

        // Buffers
        std::unique_ptr<VAO> m_vao;
        std::unique_ptr<VBO> m_vbo;
        std::unique_ptr<EBO> m_ebo;

        void Init();
    };
}
