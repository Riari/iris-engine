#include "Entity/Entity.hpp"
#include "Scene/Scene.hpp"

using namespace Iris;

Scene::Scene(int id) : m_id(id) {}

void Scene::SetActiveCamera(CameraPtr camera)
{
    m_activeCamera = std::move(camera);
}

void Scene::AddEntity(EntityPtr entity)
{
    m_entities.push_back(entity);
}

void Scene::AddEntities(std::vector<EntityPtr> entities)
{
    m_entities.insert(m_entities.end(), entities.begin(), entities.end());
}

std::vector<Scene::EntityPtr> Scene::GetEntities()
{
    return m_entities;
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
