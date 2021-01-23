#pragma once

#include "Entity/Entity.hpp"
#include "GL/Camera.hpp"
#include "LightCube.hpp"

namespace OGLDemo
{
    class ColoredCube : public OGL::Entity
    {
    public:
        explicit ColoredCube(std::string id, glm::vec3 position, glm::vec3 color, std::shared_ptr<LightCube> light);

        void Render(std::shared_ptr<OGL::Camera> camera) override;

    private:
        std::shared_ptr<LightCube> m_light;
    };
}
