#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch, float fov) :
    m_position(position),
    m_front(DEFAULT_FRONT),
    m_worldUp(worldUp),
    m_yaw(yaw),
    m_pitch(pitch),
    m_fov(fov)
{
    UpdateVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float fov) :
    Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch, fov) {}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::SetFOV(float fov)
{
    m_fov = fov;
}

void Camera::AdjustFOV(float adjustment)
{
    m_fov -= adjustment;

    if (m_fov < 1.0f) m_fov = 1.0f;
    if (m_fov > DEFAULT_FOV) m_fov = DEFAULT_FOV;
}

float Camera::GetFOV() const
{
    return m_fov;
}

void Camera::SetMoveSpeed(float moveSpeed)
{
    m_moveSpeed = moveSpeed;
}

void Camera::SetRotateSpeed(float rotateSpeed)
{
    m_rotateSpeed = rotateSpeed;
}

void Camera::SetConstrainPitch(bool constrainPitch)
{
    m_constrainPitch = constrainPitch;
}

void Camera::Move(CameraMovement direction, float deltaTime, float speedModifier)
{
    float velocity = (m_moveSpeed + speedModifier) * deltaTime;

    switch (direction)
    {
        case CameraMovement::FORWARD:
            m_position += m_front * velocity;
            break;
        case CameraMovement::BACKWARD:
            m_position -= m_front * velocity;
            break;
        case CameraMovement::LEFT:
            m_position -= m_right * velocity;
            break;
        case CameraMovement::RIGHT:
            m_position += m_right * velocity;
            break;
        case CameraMovement::UP:
            m_position += m_up * velocity;
            break;
        case CameraMovement::DOWN:
            m_position -= m_up * velocity;
            break;
    }
}

void Camera::Rotate(float xOffset, float yOffset, float deltaTime, float speedModifier)
{
    float velocity = (m_rotateSpeed + speedModifier) * deltaTime;

    m_yaw = glm::mod(m_yaw + (xOffset * velocity), 360.0f);
    m_pitch += yOffset * velocity;

    if (m_constrainPitch)
    {
        if (m_pitch > 89.0f) m_pitch = 89.0f;
        if (m_pitch < -89.0f) m_pitch = 89.0f;
    }

    UpdateVectors();
}

void Camera::UpdateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}