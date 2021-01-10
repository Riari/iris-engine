#include <Controller/CameraController.hpp>
#include <Event/EventBus.hpp>

using namespace OGL::Event;
using namespace OGL::GL;
using namespace OGL::Input;

namespace OGL::Controller
{
    CameraController::CameraController(std::shared_ptr<Camera> camera) : m_camera(std::move(camera)) {}

    std::shared_ptr<CameraController> CameraController::Create(const std::shared_ptr<Camera>& camera)
    {
        auto controller = std::make_shared<CameraController>(camera);
        return controller;
    }

    void CameraController::Handle(KeyEvent event)
    {
        auto binding = event.GetBinding();
        if (binding == nullptr) return;

        auto name = binding->GetName();
        bool pressed = event.GetAction() == GLFW_PRESS;

        if (name == "MoveForward") m_moveForward = pressed;
        if (name == "MoveBackward") m_moveBackward = pressed;
        if (name == "StrafeRight") m_strafeRight = pressed;
        if (name == "StrafeLeft") m_strafeLeft = pressed;
        if (name == "Ascend") m_ascend = pressed;
        if (name == "Descend") m_descend = pressed;
    }

//
//    void CameraController::OnMouseMove(const std::shared_ptr<MouseMoveEvent>& event)
//    {
//        if (!m_receivedFirstMouseMoveEvent)
//        {
//            m_lastCursorX = event->x;
//            m_lastCursorY = event->y;
//            m_receivedFirstMouseMoveEvent = true;
//        }
//
//        m_rotateX += event->x - m_lastCursorX;
//        m_rotateY += m_lastCursorY - event->y;
//
//        m_lastCursorX = event->x;
//        m_lastCursorY = event->y;
//    }

//    void CameraController::OnCursorPosCallback(double x, double y)
//    {
//        if (m_firstMouseMoveEvent)
//        {
//            m_lastCursorX = x;
//            m_lastCursorY = y;
//            m_firstMouseMoveEvent = false;
//        }
//
//        m_rotateX += x - m_lastCursorX;
//        m_rotateY += m_lastCursorY - y;
//
//        m_lastCursorX = x;
//        m_lastCursorY = y;
//    }
//
//    void CameraController::OnScrollCallback(double x, double y)
//    {
//        m_camera->AdjustFOV(y);
//    }

    void CameraController::Update(double deltaTime)
    {
        m_camera->Rotate(m_rotateX, m_rotateY, deltaTime);
        m_rotateX = 0.0f;
        m_rotateY = 0.0f;

        float speedModifier = InputManager::IsShiftHeld() ? 4.0f : 0.0f;

        if (m_moveForward) m_camera->Move(CameraMovement::FORWARD, deltaTime, speedModifier);
        if (m_moveBackward) m_camera->Move(CameraMovement::BACKWARD, deltaTime, speedModifier);
        if (m_strafeRight) m_camera->Move(CameraMovement::RIGHT, deltaTime, speedModifier);
        if (m_strafeLeft) m_camera->Move(CameraMovement::LEFT, deltaTime, speedModifier);
        if (m_ascend) m_camera->Move(CameraMovement::UP, deltaTime, speedModifier);
        if (m_descend) m_camera->Move(CameraMovement::DOWN, deltaTime, speedModifier);
    }
}
