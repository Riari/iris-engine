#include <utility>

#include <glm/ext.hpp>

#include "Entity/RenderableEntity.hpp"

using namespace OGL;

RenderableEntity::RenderableEntity(int id, glm::vec3 position) : Entity(id, position), m_model(glm::mat4(1.0f))
{
    m_model = glm::translate(m_model, m_position);
}

void RenderableEntity::SetVAO(const VAO &vao)
{
    m_vao = vao;
}

void RenderableEntity::SetShaderProgram(std::shared_ptr<ShaderProgram> program)
{
    m_shaderProgram = std::move(program);
}

void RenderableEntity::SetVisible(bool visible)
{
    m_visible = visible;
}

void RenderableEntity::Rotate(float degrees, glm::vec3 v)
{
    m_model = glm::rotate(m_model, glm::radians(degrees), v);
}

void RenderableEntity::Translate(glm::vec3 v)
{
    m_model = glm::translate(m_model, v);
}

void RenderableEntity::Scale(glm::vec3 v)
{
    m_model = glm::scale(m_model, v);
}

bool RenderableEntity::GetVisible() const
{
    return m_visible;
}
