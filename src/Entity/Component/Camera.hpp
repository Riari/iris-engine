#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace Iris
{
    const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 DEFAULT_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
    const glm::vec3 DEFAULT_WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

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
        glm::vec3 up{};
        glm::vec3 right{};
        glm::vec3 worldUp = DEFAULT_WORLD_UP;

        float yaw = DEFAULT_YAW;
        float pitch = DEFAULT_PITCH;
        float fov = DEFAULT_FOV;

        float aspectRatio;

        float clipNear = DEFAULT_CLIP_NEAR;
        float clipFar = DEFAULT_CLIP_FAR;

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
