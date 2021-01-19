#include "Entity/Entity.hpp"

#include <utility>

using namespace OGL;

Entity::Entity(std::string id, glm::vec3 position) : m_id(std::move(id)), m_position(position) {}

std::string Entity::GetID() const
{
    return m_id;
}

void Entity::SetPosition(glm::vec3 position)
{
    m_position = position;
}

glm::vec3 Entity::GetPosition()
{
    return m_position;
}
