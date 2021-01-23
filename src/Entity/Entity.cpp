#include <utility>

#include <glm/ext.hpp>

#include "Entity/Entity.hpp"

using namespace OGL;

Entity::Entity(std::string id, glm::vec3 position) : m_id(std::move(id)), m_transform(std::make_unique<Transform>(position))
{}

void Entity::SetVAO(const VAO &vao)
{
    m_vao = vao;
}

void Entity::SetShaderProgram(std::shared_ptr<ShaderProgram> program)
{
    m_shaderProgram = std::move(program);
}

bool Entity::IsVisible() const
{
    return m_visible;
}

Transform& Entity::GetTransform()
{
    return *m_transform;
}
