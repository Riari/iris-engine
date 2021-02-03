#pragma once

#include <memory>

#include "Controller/Controller.hpp"
#include "Event/Event.hpp"
#include "GL/Camera.hpp"
#include "Input/InputHandler.hpp"
#include "Input/InputManager.hpp"
#include "Input/KeyEvent.hpp"
#include "Scene/Scene.hpp"
#include "Window/FrameBufferEvent.hpp"
#include "Window/Window.hpp"
#include "Window/WindowEventHandler.hpp"

namespace IrisDemo
{
    class CameraController :
            public Iris::Controller,
            public Iris::WindowEventHandler<Iris::FrameBufferEvent>,
            public Iris::InputHandler<Iris::KeyEvent>,
            public Iris::InputHandler<Iris::MouseMoveEvent>,
            public Iris::InputHandler<Iris::MouseScrollEvent>
    {
    public:
        explicit CameraController(int id, Iris::Scene::CameraPtr camera);

        void Handle(Iris::FrameBufferEvent) override;
        void Handle(Iris::KeyEvent) override;
        void Handle(Iris::MouseMoveEvent) override;
        void Handle(Iris::MouseScrollEvent) override;

        void Update(Iris::Window&) override;

    private:
        Iris::Scene::CameraPtr m_camera;

        bool m_moveForward = false;
        bool m_moveBackward = false;
        bool m_strafeLeft = false;
        bool m_strafeRight = false;
        bool m_ascend = false;
        bool m_descend = false;

        bool m_receivedFirstMouseMoveEvent = false;
        float m_rotateX, m_rotateY, m_lastCursorX, m_lastCursorY;
    };
}
