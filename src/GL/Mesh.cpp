#include <utility>
#include <string>
#include "Mesh.hpp"

using namespace Iris::GL;

Mesh::Mesh(std::vector<VertexData> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures) :
    m_vertices(std::move(vertices)),
    m_indices(std::move(indices)),
    m_textures(std::move(textures))
{
    Init();
}

void Mesh::Draw(const std::shared_ptr<ShaderProgram>& program)
{
    unsigned int diffuseIndex = 0, specularIndex = 0, emissionIndex = 0, normalIndex = 0, heightIndex = 0;
    const static std::string prefix = "material.";

    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        m_textures[i].texture->Bind(GL_TEXTURE0 + i);

        std::string name, typeIndex;
        switch (m_textures[i].type)
        {
            case Diffuse:
                name = "diffuse";
                typeIndex = std::to_string(diffuseIndex++);
                break;
            case Specular:
                name = "specular";
                typeIndex = std::to_string(specularIndex++);
                break;
            case Emission:
                name = "emission";
                typeIndex = std::to_string(emissionIndex++);
                break;
            case Normal:
                name = "normal";
                typeIndex = std::to_string(normalIndex++);
                break;
            case Height:
                name = "height";
                typeIndex = std::to_string(heightIndex++);
                break;
        }

        program->SetUniformFloat(prefix + name + typeIndex, i);
    }

    m_vao->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
    m_vao->Unbind();
}

void Mesh::Init()
{
    // TODO: Enable sharing of buffers between meshes

    m_vao = std::make_unique<VAO>();
    m_vbo = std::make_unique<VBO>();
    m_ebo = std::make_unique<EBO>();

    m_vao->Bind();

    m_vbo->Bind();
    m_vbo->SetData(m_vertices.size() * sizeof(VertexData), &m_vertices[0], GL_STATIC_DRAW);

    m_ebo->Bind();
    m_ebo->SetData(m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // Vertex positions
    VAO::SetAttrPointer(0, 3, sizeof(VertexData), (void*)0);

    // Normals
    VAO::SetAttrPointer(1, 3, sizeof(VertexData), (void*)offsetof(VertexData, normal));

    // Texture coords
    VAO::SetAttrPointer(2, 2, sizeof(VertexData), (void*)offsetof(VertexData, texCoords));

    // Tangents
    VAO::SetAttrPointer(3, 3, sizeof(VertexData), (void*)offsetof(VertexData, tangent));

    // Bitangents
    VAO::SetAttrPointer(4, 3, sizeof(VertexData), (void*)offsetof(VertexData, bitangent));

    VAO::Unbind();
}
