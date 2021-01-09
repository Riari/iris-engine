#include "CameraController.h"
#include "../Event/EventBus.h"

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

    void CameraController::Handle(KeyPress event)
    {
        m_moveX, m_moveY, m_moveZ = 0;

        if (event.GetAction() != Action::Hold) return;

        auto binding = event.GetBinding();
        if (binding == nullptr) return;

        if (binding->GetName() == "MoveForward") m_moveZ = Positive;
        if (binding->GetName() == "MoveBackward") m_moveZ = Negative;
        if (binding->GetName() == "StrafeRight") m_moveX = Positive;
        if (binding->GetName() == "StrafeLeft") m_moveX = Negative;
        if (binding->GetName() == "Ascend") m_moveY = Positive;
        if (binding->GetName() == "Descend") m_moveY = Negative;
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

        float speedModifier = InputManager::IsShiftHeld() ? 4.0f : 1.0f;

        switch (m_moveX)
        {
            case Positive: m_camera->Move(CameraMovement::RIGHT, deltaTime, speedModifier); break;
            case Negative: m_camera->Move(CameraMovement::LEFT, deltaTime, speedModifier); break;
        }

        switch (m_moveY)
        {
            case Positive: m_camera->Move(CameraMovement::UP, deltaTime, speedModifier); break;
            case Negative: m_camera->Move(CameraMovement::DOWN, deltaTime, speedModifier); break;
        }

        switch (m_moveZ)
        {
            case Positive: m_camera->Move(CameraMovement::FORWARD, deltaTime, speedModifier); break;
            case Negative: m_camera->Move(CameraMovement::BACKWARD, deltaTime, speedModifier); break;
        }
    }
}
