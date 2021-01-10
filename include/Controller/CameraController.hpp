#pragma once

#include <memory>

#include "Event/Event.hpp"
#include "GL/Camera.hpp"
#include "Input/InputManager.hpp"
#include "Input/InputHandler.hpp"
#include "Input/KeyEvent.hpp"

using namespace OGL::GL;
using namespace OGL::Event;
using namespace OGL::Input;

namespace OGL::Controller
{
    class CameraController : public InputHandler<KeyEvent>
    {
    public:
        explicit CameraController(std::shared_ptr<Camera> camera);

        static std::shared_ptr<CameraController> Create(const std::shared_ptr<Camera>& camera);

        void Handle(KeyEvent) override;

        void Update(double deltaTime);

    private:
        std::shared_ptr<Camera> m_camera;

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
