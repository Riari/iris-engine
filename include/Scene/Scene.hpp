#pragma once

#include <map>
#include <memory>

#include "Controller/Controller.hpp"
#include "Entity/Entity.hpp"
#include "GL/Renderer.hpp"
#include "Window/FrameBufferEvent.hpp"
#include "Window/Window.hpp"
#include "Window/WindowEventHandler.hpp"

namespace OGL
{
    class Scene
    {
    public:
        typedef std::shared_ptr<Entity> EntityPtr;
        typedef std::shared_ptr<Controller> ControllerPtr;
        typedef std::map<const int, ControllerPtr> ControllerMap;
        typedef std::shared_ptr<Camera> CameraPtr;

        explicit Scene(int);

        void SetActiveCamera(CameraPtr);

        void AddEntity(EntityPtr);
        void AddEntities(std::vector<EntityPtr>);
        std::vector<EntityPtr> GetEntities();

        void AddController(ControllerPtr);
        ControllerPtr GetController(int);
        ControllerMap GetControllers();
        void RemoveController(int);

        void Update(Window&);
        void Render(Window&);

    private:
        int m_id;

        std::shared_ptr<Camera> m_activeCamera;
        std::vector<std::shared_ptr<Entity>> m_entities;
        ControllerMap m_controllers;
    };
}