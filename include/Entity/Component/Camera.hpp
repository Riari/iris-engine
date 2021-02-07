#pragma once

#include <glm/ext.hpp>
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

    struct Camera
    {
        bool constrainPitch = true;

        glm::vec3 position = DEFAULT_POSITION;
        glm::vec3 front = DEFAULT_FRONT;
        glm::vec3 up = DEFAULT_UP;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw = DEFAULT_YAW;
        float pitch = DEFAULT_PITCH;
        float fov = DEFAULT_FOV;

        float aspectRatio;

        float clipNear = DEFAULT_CLIP_NEAR;
        float clipFar = DEFAULT_CLIP_FAR;

        void AdjustFOV(float adjustment)
        {
            fov -= adjustment;

            if (fov < 1.0f) fov = 1.0f;
            if (fov > DEFAULT_FOV) fov = DEFAULT_FOV;
        }

        void Move(CameraMovement direction, double deltaTime, double moveSpeed)
        {
            float velocity = moveSpeed * deltaTime;

            switch (direction)
            {
                case CameraMovement::FORWARD:
                    position += front * velocity;
                    break;
                case CameraMovement::BACKWARD:
                    position -= front * velocity;
                    break;
                case CameraMovement::LEFT:
                    position -= right * velocity;
                    break;
                case CameraMovement::RIGHT:
                    position += right * velocity;
                    break;
                case CameraMovement::UP:
                    position += up * velocity;
                    break;
                case CameraMovement::DOWN:
                    position -= up * velocity;
                    break;
            }
        }

        void Rotate(float xOffset, float yOffset, double deltaTime, double rotateSpeed)
        {
            float velocity = rotateSpeed * deltaTime;

            yaw = glm::mod(yaw + (xOffset * velocity), 360.0f);
            pitch += yOffset * velocity;

            if (constrainPitch)
            {
                if (pitch > 89.0f) pitch = 89.0f;
                if (pitch < -89.0f) pitch = -89.0f;
            }

            UpdateVectors();
        }

        void UpdateVectors()
        {
            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(front);

            right = glm::normalize(glm::cross(front, worldUp));
            up = glm::normalize(glm::cross(right, front));
        }

        [[nodiscard]] glm::mat4 GetProjectionMatrix() const
        {
            return glm::perspective(glm::radians(fov), aspectRatio, clipNear, clipFar);
        }

        [[nodiscard]] glm::mat4 GetViewMatrix() const
        {
            return glm::lookAt(position, position + front, up);
        }
    };
}