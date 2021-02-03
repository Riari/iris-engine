#pragma once

#include <glm/glm.hpp>

namespace Iris
{
    class Transform
    {
    public:
        const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f);
        const float DEFAULT_ROTATION = 0.0f;
        const glm::vec3 DEFAULT_SCALE = glm::vec3(1.0f);
        const glm::mat4 IDENTITY = glm::mat4(1.0f);

        explicit Transform(glm::vec3);

        void SetPosition(glm::vec3);
        void SetRotation(float);
        void SetScale(float);
        void SetScale(glm::vec3);

        void Move(glm::vec3);
        void Rotate(float);
        void Scale(float);
        void Scale(glm::vec3);

        glm::vec3 GetPosition();
        [[nodiscard]] float GetRotation() const;
        glm::vec3 GetScale();
        glm::mat4 GetModel();

    private:
        glm::vec3 m_position = DEFAULT_POSITION;
        float m_rotation = DEFAULT_ROTATION;
        glm::vec3 m_scale = DEFAULT_SCALE;
        bool m_isDirty = true;
        glm::mat4 m_model = IDENTITY;
    };
}