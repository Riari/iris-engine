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

void CameraController::Handle(OGL::MouseMoveEvent event)
{
    auto x = event.GetX();
    auto y = event.GetY();

    if (!m_receivedFirstMouseMoveEvent)
    {
        m_lastCursorX = x;
        m_lastCursorY = y;
        m_receivedFirstMouseMoveEvent = true;
    }

    m_rotateX += x - m_lastCursorX;
    m_rotateY += m_lastCursorY - y;

    m_lastCursorX = x;
    m_lastCursorY = y;
}

void CameraController::Handle(OGL::MouseScrollEvent event)
{
    m_camera->AdjustFOV(event.GetY());
}

void CameraController::Update(double deltaTime)
{
    m_camera->Rotate(m_rotateX, m_rotateY, deltaTime);
    m_rotateX = 0.0f;
    m_rotateY = 0.0f;

    float speedModifier = OGL::InputManager::IsAltDown() ? 4.0f : 0.0f;

    if (m_moveForward) m_camera->Move(OGL::CameraMovement::FORWARD, deltaTime, speedModifier);
    if (m_moveBackward) m_camera->Move(OGL::CameraMovement::BACKWARD, deltaTime, speedModifier);
    if (m_strafeRight) m_camera->Move(OGL::CameraMovement::RIGHT, deltaTime, speedModifier);
    if (m_strafeLeft) m_camera->Move(OGL::CameraMovement::LEFT, deltaTime, speedModifier);
    if (m_ascend) m_camera->Move(OGL::CameraMovement::UP, deltaTime, speedModifier);
    if (m_descend) m_camera->Move(OGL::CameraMovement::DOWN, deltaTime, speedModifier);
}
