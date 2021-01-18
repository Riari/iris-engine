#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "GL/VAO.hpp"
#include "GL/VBO.hpp"
#include "GL/Shader/ShaderProgram.hpp"

namespace OGL
{
    class Entity
    {
    public:
        Entity(int id, glm::vec3 position);

        [[nodiscard]] int GetID() const;
        void SetPosition(glm::vec3);
        glm::vec3 GetPosition();

    protected:
        int m_id;
        glm::vec3 m_position;
    };
}