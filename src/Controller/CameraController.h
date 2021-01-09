#pragma once

#include <memory>

#include "../Event/Event.h"
#include "../GL/Camera.h"
#include "../Input/InputManager.h"
#include "../Input/InputHandler.h"
#include "../Input/KeyPress.h"

using namespace OGL::GL;
using namespace OGL::Event;
using namespace OGL::Input;

namespace OGL::Controller
{
    class CameraController : public InputHandler<KeyPress>
    {
    public:
        explicit CameraController(std::shared_ptr<Camera> camera);

        static std::shared_ptr<CameraController> Create(const std::shared_ptr<Camera>& camera);

        void Handle(KeyPress) override;

        void Update(double deltaTime);

    private:
        static constexpr int Positive = 1;
        static constexpr int Negative = -1;

        std::shared_ptr<Camera> m_camera;

        int m_moveX, m_moveZ, m_moveY = 0;

        bool m_receivedFirstMouseMoveEvent = true;
        float m_rotateX, m_rotateY, m_lastCursorX, m_lastCursorY;
    };
}
