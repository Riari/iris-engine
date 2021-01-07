#pragma once

#include <memory>

#include "../Event/Event.h"
#include "../GL/Camera.h"
#include "../Input/InputManager.h"
#include "../Window/Handler/CursorPosHandler.h"
#include "../Window/Handler/KeyHandler.h"
#include "../Window/Handler/ScrollHandler.h"

using namespace OGL::GL;
using namespace OGL::Event;

namespace OGL::Controller
{
    class CameraController
    {
    public:
        explicit CameraController(std::shared_ptr<Camera> camera);

        static std::shared_ptr<CameraController> Create(const std::shared_ptr<Camera>& camera);

//        bool HandleEvent(std::shared_ptr<Event::Event>) override;

        void Update(double deltaTime);

    private:
        std::shared_ptr<Camera> m_camera;

//        void OnKeyPress(const std::shared_ptr<KeyPressEvent>&);
//        void OnMouseMove(const std::shared_ptr<MouseMoveEvent>&);

        bool m_receivedFirstMouseMoveEvent = true;
        float m_rotateX, m_rotateY, m_lastCursorX, m_lastCursorY;
    };
}
