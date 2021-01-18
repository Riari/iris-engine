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

namespace OGLDemo
{
    class CameraController :
            public OGL::Controller,
            public OGL::WindowEventHandler<OGL::FrameBufferEvent>,
            public OGL::InputHandler<OGL::KeyEvent>,
            public OGL::InputHandler<OGL::MouseMoveEvent>,
            public OGL::InputHandler<OGL::MouseScrollEvent>
    {
    public:
        explicit CameraController(int id, OGL::Scene::CameraPtr camera);

        void Handle(OGL::FrameBufferEvent) override;
        void Handle(OGL::KeyEvent) override;
        void Handle(OGL::MouseMoveEvent) override;
        void Handle(OGL::MouseScrollEvent) override;

        void Update(OGL::Window&) override;

    private:
        OGL::Scene::CameraPtr m_camera;

        bool m_moveForward = false;
        bool m_moveBackward = false;
        bool m_strafeLeft = false;
        bool m_strafeRight = false;
        bool m_ascend = false;
        bool m_descend = false;

        bool m_receivedFirstMouseMoveEvent = true;
        float m_rotateX, m_rotateY, m_lastCursorX, m_lastCursorY;
    };
}
