#pragma once

#include <glm/glm.hpp>

namespace Iris
{
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

    const float DEFAULT_YAW = -90.0f;
    const float DEFAULT_PITCH = 0.0f;
    const float DEFAULT_FOV = 45.0f;

    const float DEFAULT_CLIP_NEAR = 0.1f;
    const float DEFAULT_CLIP_FAR = 100.0f;

    class Camera
    {
    public:
        explicit Camera(float aspectRatio, glm::vec3 position = DEFAULT_POSITION, glm::vec3 up = DEFAULT_UP, float yaw = DEFAULT_YAW,
                        float pitch = DEFAULT_PITCH, float fov = DEFAULT_FOV);

        glm::vec3 GetPosition();

        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix();

        void SetAspectRatio(float ratio);
        void SetFOV(float fov);
        void AdjustFOV(float adjustment);

        void SetMoveSpeed(double moveSpeed);
        void SetRotateSpeed(double rotateSpeed);
        void SetConstrainPitch(bool constrainPitch);

        void Move(CameraMovement direction, double deltaTime, double speedModifier = 0.0);
        void Rotate(float xOffset, float yOffset, double deltaTime, double speedModifier = 0.0);

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

        float m_aspectRatio;

        float m_clipNear = DEFAULT_CLIP_NEAR;
        float m_clipFar = DEFAULT_CLIP_FAR;

        double m_moveSpeed = 2.5f;
        double m_rotateSpeed = 2.5f;

        void UpdateVectors();
    };
}
