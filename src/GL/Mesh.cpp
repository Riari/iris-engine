#include <utility>
#include <string>

#include "GL/Mesh.hpp"

using namespace Iris;

Mesh::Mesh(std::vector<GLVertex> vertices, std::vector<unsigned int> indices, std::vector<GLTexture> textures) :
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
        glActiveTexture(GL_TEXTURE0 + i);

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
        glBindTexture(GL_TEXTURE_2D, m_textures[i].texture->GetID());
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::Init()
{
    // TODO: Use VAO/VBO/EBO objects and enable sharing of them
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLVertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)0);

    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, normal));

    // Vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, texCoords));

    glBindVertexArray(0);
}
