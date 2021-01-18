#pragma once

#include <map>
#include <memory>

#include "Controller/Controller.hpp"
#include "Entity/Entity.hpp"
#include "Entity/RenderableEntity.hpp"
#include "GL/Renderer.hpp"
#include "Window/FrameBufferEvent.hpp"
#include "Window/Window.hpp"
#include "Window/WindowEventHandler.hpp"

namespace OGL
{
    class Scene
    {
    public:
        typedef std::shared_ptr<RenderableEntity> EntityPtr;
        typedef std::map<const int, EntityPtr> EntityMap;
        typedef std::shared_ptr<Controller> ControllerPtr;
        typedef std::map<const int, ControllerPtr> ControllerMap;
        typedef std::shared_ptr<Camera> CameraPtr;

        explicit Scene(int);

        void SetActiveCamera(CameraPtr);

        void AddEntity(EntityPtr);
        EntityPtr GetEntity(int);
        std::vector<EntityPtr> GetEntities();
        void RemoveEntity(int);

        void AddController(ControllerPtr);
        ControllerPtr GetController(int);
        ControllerMap GetControllers();
        void RemoveController(int);

        void Update(Window&);
        void Render(Window&);

    private:
        int m_id;

        std::shared_ptr<Camera> m_activeCamera;
        EntityMap m_entities;
        ControllerMap m_controllers;
    };
}