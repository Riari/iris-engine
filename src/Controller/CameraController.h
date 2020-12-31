#pragma once

#include <memory>

#include "../GL/Camera.h"
#include "../Input/InputManager.h"
#include "../Window/Handler/CursorPosHandler.h"
#include "../Window/Handler/KeyHandler.h"
#include "../Window/Handler/ScrollHandler.h"

namespace OGL::Controller
{
    class CameraController : public OGL::Window::CursorPosHandler, public OGL::Window::ScrollHandler
    {
    public:
        explicit CameraController(std::shared_ptr<OGL::GL::Camera> camera, std::shared_ptr<OGL::Input::InputManager> input);

        void OnCursorPosCallback(double x, double y) override;

        void OnScrollCallback(double x, double y) override;

        void Update(double deltaTime);

    private:
        std::shared_ptr<OGL::GL::Camera> m_camera;
        std::shared_ptr<OGL::Input::InputManager> m_input;

        bool m_firstCursorPosCallback = true;
        float m_rotateX, m_rotateY, m_lastCursorX, m_lastCursorY;
    };
}
