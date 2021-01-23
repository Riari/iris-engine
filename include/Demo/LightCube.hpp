#pragma once

#include "Entity/Entity.hpp"
#include "GL/Camera.hpp"

namespace OGLDemo
{
    class LightCube : public OGL::Entity
    {
    public:
        explicit LightCube(std::string id, glm::vec3 position, glm::vec3 emissionColor);

        void Render(std::shared_ptr<OGL::Camera> camera) override;

        glm::vec3 GetEmissionColor();

    private:
        glm::vec3 m_emissionColor;
    };
}
