#pragma once

#include <glm/glm.hpp>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 DEFAULT_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 DEFAULT_UP = glm::vec3(0.0f, 1.0f, 0.0f);

const float DEFAULT_CAM_YAW = -90.0f;
const float DEFAULT_CAM_PITCH = 0.0f;
const float DEFAULT_CAM_FOV = 45.0f;

class Camera
{
public:
    explicit Camera(glm::vec3 position = DEFAULT_POSITION, glm::vec3 up = DEFAULT_UP, float yaw = DEFAULT_CAM_YAW,
                    float pitch = DEFAULT_CAM_PITCH, float fov = DEFAULT_CAM_FOV);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float fov);

    glm::mat4 GetViewMatrix();

    void SetFOV(float fov);
    void AdjustFOV(float adjustment);
    [[nodiscard]] float GetFOV() const;

    void SetMoveSpeed(float moveSpeed);
    void SetRotateSpeed(float rotateSpeed);
    void SetConstrainPitch(bool constrainPitch);

    void Move(CameraMovement direction, float deltaTime, float speedModifier = 0.0f);
    void Rotate(float xOffset, float yOffset, float deltaTime, float speedModifier = 0.0f);

private:
    bool m_constrainPitch = true;

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up{};
    glm::vec3 m_right{};
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;
    float m_fov;

    float m_moveSpeed = 2.5f;
    float m_rotateSpeed = 2.5f;

    void UpdateVectors();
};