#pragma once

#include "Entity/RenderableEntity.hpp"
#include "GL/Camera.hpp"

namespace OGLDemo
{
    class LightCube : public OGL::RenderableEntity
    {
    public:
        explicit LightCube(std::string id, glm::vec3 position);

        void Render(std::shared_ptr<OGL::Camera> camera) override;
    };
}
