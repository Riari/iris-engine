#pragma once

#include "Scene/Scene.hpp"
#include "Window/Window.hpp"

namespace OGL
{
    class RenderableEntity;

    class Renderer
    {
    public:
        static void EnableCapability(unsigned int capability);
        static void SetViewport(int w, int h);
        static void Clear(glm::vec4 color = glm::vec4(0.1f, 0.1f, 0.14f, 1.0f));
        static void Draw(const std::map<const int, std::shared_ptr<RenderableEntity>>& entities, const std::shared_ptr<Camera>& camera);
    };
}