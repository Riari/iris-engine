#pragma once

#include "Entity/RenderableEntity.hpp"
#include "GL/Camera.hpp"

namespace OGLDemo
{
    class ColoredCube : public OGL::RenderableEntity
    {
    public:
        explicit ColoredCube(int id, glm::vec3 position, glm::vec3 color, glm::vec3 lightColor, glm::vec3 lightPos);

        void Render(std::shared_ptr<OGL::Camera> camera) override;
    };
}
