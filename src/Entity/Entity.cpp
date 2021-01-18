#include "Entity/Entity.hpp"

using namespace OGL;

Entity::Entity(int id, glm::vec3 position) : m_id(id), m_position(position) {}

int Entity::GetID() const
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
