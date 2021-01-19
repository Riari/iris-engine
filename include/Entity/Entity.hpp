#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "GL/VAO.hpp"
#include "GL/VBO.hpp"
#include "GL/Shader/ShaderProgram.hpp"

namespace OGL
{
    class Entity
    {
    public:
        explicit Entity(std::string id, glm::vec3 position);

        [[nodiscard]] std::string GetID() const;
        void SetPosition(glm::vec3);
        glm::vec3 GetPosition();

    protected:
        std::string m_id;
        glm::vec3 m_position;
    };
}