#include "CameraController.h"
#include "../Event/EventBus.h"

using namespace OGL::Event;
using namespace OGL::GL;
using namespace OGL::Input;

namespace OGL::Controller
{
    CameraController::CameraController(std::shared_ptr<Camera> camera) : m_camera(std::move(camera))
    {}

    std::shared_ptr<CameraController> CameraController::Create(const std::shared_ptr<Camera>& camera)
    {
        auto controller = std::make_shared<CameraController>(camera);
//        EventBus::Subscribe(EventType::KeyPress, controller);
//        EventBus::Subscribe(EventType::MouseMove, controller);
        return controller;
    }

//    bool CameraController::HandleEvent(std::shared_ptr<Event::Event> event)
//    {
//        switch (event->GetType())
//        {
//            case KeyPress:
//                OnKeyPress(std::static_pointer_cast<KeyPressEvent>(event));
//                return true;
//            case MouseMove:
//                OnMouseMove(std::static_pointer_cast<MouseMoveEvent>(event));
//                return true;
//            default: return false;
//        }
//    }
//
//    void CameraController::OnKeyPress(const std::shared_ptr<KeyPressEvent>& event)
//    {
//
//    }
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

//        float speedModifier = m_input->IsShiftHeld() ? 4.0f : 0.0f;
//
//        if (m_input->IsHeld(m_input->MoveForward)) m_camera->Move(CameraMovement::FORWARD, deltaTime, speedModifier);
//        if (m_input->IsHeld(m_input->MoveBackward)) m_camera->Move(CameraMovement::BACKWARD, deltaTime, speedModifier);
//        if (m_input->IsHeld(m_input->StrafeLeft)) m_camera->Move(CameraMovement::LEFT, deltaTime, speedModifier);
//        if (m_input->IsHeld(m_input->StrafeRight)) m_camera->Move(CameraMovement::RIGHT, deltaTime, speedModifier);
//        if (m_input->IsHeld(m_input->GoUp)) m_camera->Move(CameraMovement::UP, deltaTime, speedModifier);
//        if (m_input->IsHeld(m_input->GoDown)) m_camera->Move(CameraMovement::DOWN, deltaTime, speedModifier);
    }
}
