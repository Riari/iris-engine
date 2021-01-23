#include <glad/glad.h>

#include "GL/Renderer.hpp"

using namespace OGL;

void Renderer::EnableCapability(unsigned int capability)
{
    glEnable(capability);
}

void Renderer::SetViewport(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Renderer::Clear(glm::vec4 color)
{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const std::vector<std::shared_ptr<Entity>>& entities, const Scene::CameraPtr& camera)
{
    for (const auto& entity : entities)
    {
        if (entity->IsVisible()) entity->Render(camera);
    }
}
