#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "GL/Camera.hpp"
#include "GL/Transform.hpp"
#include "GL/VAO.hpp"
#include "GL/VBO.hpp"
#include "GL/Shader/ShaderProgram.hpp"

namespace Iris
{
    class Entity
    {
    public:
        Entity(std::string id, glm::vec3 position);

        void SetVAO(const VAO&);
        void SetShaderProgram(std::shared_ptr<ShaderProgram>);

        [[nodiscard]] bool IsVisible() const;
        Transform& GetTransform();

        virtual void Render(std::shared_ptr<Camera> camera) = 0;

    protected:
        std::string m_id;

        VAO m_vao;
        std::shared_ptr<ShaderProgram> m_shaderProgram;

        bool m_visible = true;
        std::unique_ptr<Transform> m_transform;
    };
}