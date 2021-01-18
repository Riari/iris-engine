#pragma once

#include "Entity.hpp"
#include "GL/Camera.hpp"
#include "Window/Window.hpp"

namespace OGL
{
    class RenderableEntity : public Entity
    {
    public:
        RenderableEntity(int id, glm::vec3 position);

        void SetVAO(const VAO&);
        void SetShaderProgram(std::shared_ptr<ShaderProgram>);

        void SetVisible(bool);
        void Rotate(float degrees, glm::vec3 v = glm::vec3(1, 1, 1));
        void Translate(glm::vec3);
        void Scale(glm::vec3);

        [[nodiscard]] bool GetVisible() const;

        virtual void Render(std::shared_ptr<Camera> camera) = 0;

    protected:
        bool m_visible = true;

        VAO m_vao;

        std::shared_ptr<ShaderProgram> m_shaderProgram;

        glm::mat4 m_model;
    };
}