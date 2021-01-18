#include "Entity/RenderableEntity.hpp"
#include "Scene/Scene.hpp"

using namespace OGL;

Scene::Scene(int id) : m_id(id) {}

void Scene::SetActiveCamera(CameraPtr camera)
{
    m_activeCamera = std::move(camera);
}

void Scene::AddEntity(EntityPtr entity)
{
    m_entities.insert(std::pair(entity->GetID(), entity));
}

Scene::EntityPtr Scene::GetEntity(int id)
{
    return m_entities[id];
}

std::vector<Scene::EntityPtr> Scene::GetEntities()
{
    std::vector<EntityPtr> entities;
    for (auto & v : m_entities) entities.push_back(v.second);
    return entities;
}

void Scene::RemoveEntity(int id)
{
    m_entities.erase(id);
}

void Scene::AddController(ControllerPtr controller)
{
    m_controllers.insert(std::pair(controller->GetID(), controller));
}

Scene::ControllerPtr Scene::GetController(int id)
{
    return m_controllers[id];
}

Scene::ControllerMap Scene::GetControllers()
{
    return m_controllers;
}

void Scene::RemoveController(int id)
{
    m_controllers.erase(id);
}

void Scene::Update(Window &window)
{
    for (const auto& [id, controller] : m_controllers)
    {
        controller->Update(window);
    }
}

void Scene::Render(Window &window)
{
    Renderer::Clear();
    Renderer::Draw(m_entities, m_activeCamera);
    window.SwapBuffers();
}
