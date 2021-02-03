#include <glm/ext.hpp>

#include "GL/Transform.hpp"

using namespace Iris;

Transform::Transform(glm::vec3 position) : m_position(position) {}

void Transform::SetPosition(glm::vec3 position)
{
    m_position = position;
    m_isDirty = true;
}

void Transform::SetRotation(float rotation)
{
    m_rotation = rotation;
    m_isDirty = true;
}

void Transform::SetScale(float scale)
{
    SetScale(glm::vec3(scale));
}

void Transform::SetScale(glm::vec3 scale)
{
    m_scale = scale;
    m_isDirty = true;
}

void Transform::Move(glm::vec3 position)
{
    SetPosition(m_position + position);
}

void Transform::Rotate(float rotation)
{
    SetRotation(m_rotation + rotation);
}

void Transform::Scale(float scale)
{
    SetScale(m_scale + scale);
}

void Transform::Scale(glm::vec3 scale)
{
    SetScale(m_scale + scale);
}

glm::vec3 Transform::GetPosition()
{
    return m_position;
}

float Transform::GetRotation() const
{
    return m_rotation;
}

glm::vec3 Transform::GetScale()
{
    return m_scale;
}

glm::mat4 Transform::GetModel()
{
    if (m_isDirty)
    {
        m_model = IDENTITY;
        m_model = glm::translate(m_model, m_position);
        m_model = glm::rotate(m_model, m_rotation, glm::vec3(1.0f));
        m_model = glm::scale(m_model, m_scale);
        m_isDirty = false;
    }

    return m_model;
}

