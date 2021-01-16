#include "Demo/CameraController.hpp"
#include "Demo/Keys.hpp"
#include "Event/EventBus.hpp"
#include "Window/Window.hpp"

using namespace OGLDemo;

CameraController::CameraController(std::shared_ptr<OGL::Camera> camera) : m_camera(std::move(camera)) {}

std::shared_ptr<CameraController> CameraController::Create(const std::shared_ptr<OGL::Camera>& camera)
{
    auto controller = std::make_shared<CameraController>(camera);
    return controller;
}

void CameraController::Handle(OGL::KeyEvent event)
{
    auto binding = event.GetBinding();
    if (binding == nullptr) return;

    bool pressed = event.GetAction() == GLFW_PRESS;

    switch (binding->GetID())
    {
        case Keys::MoveForward: m_moveForward = pressed; break;
        case Keys::MoveBackward: m_moveBackward = pressed; break;
        case Keys::StrafeRight: m_strafeRight = pressed; break;
        case Keys::StrafeLeft: m_strafeLeft = pressed; break;
        case Keys::Ascend: m_ascend = pressed; break;
        case Keys::Descend: m_descend = pressed; break;
    }
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

    float speedModifier = OGL::InputManager::IsShiftHeld() ? 4.0f : 0.0f;

    if (m_moveForward) m_camera->Move(OGL::CameraMovement::FORWARD, deltaTime, speedModifier);
    if (m_moveBackward) m_camera->Move(OGL::CameraMovement::BACKWARD, deltaTime, speedModifier);
    if (m_strafeRight) m_camera->Move(OGL::CameraMovement::RIGHT, deltaTime, speedModifier);
    if (m_strafeLeft) m_camera->Move(OGL::CameraMovement::LEFT, deltaTime, speedModifier);
    if (m_ascend) m_camera->Move(OGL::CameraMovement::UP, deltaTime, speedModifier);
    if (m_descend) m_camera->Move(OGL::CameraMovement::DOWN, deltaTime, speedModifier);
}
