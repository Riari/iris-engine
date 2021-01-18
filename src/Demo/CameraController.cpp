#include "Demo/CameraController.hpp"
#include "Demo/Keys.hpp"
#include "Event/EventBus.hpp"
#include "Window/Window.hpp"

using namespace OGLDemo;

CameraController::CameraController(int id, OGL::Scene::CameraPtr camera) : Controller(id), m_camera(std::move(camera)) {}

void CameraController::Handle(OGL::FrameBufferEvent event)
{
    m_camera->SetAspectRatio((float) event.GetWidth() / (float) event.GetHeight());
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

void CameraController::Update(OGL::Window &window)
{
    m_camera->Rotate(m_rotateX, m_rotateY, window.GetDeltaTime());
    m_rotateX = 0.0f;
    m_rotateY = 0.0f;

    float speedModifier = OGL::InputManager::IsAltDown() ? 4.0f : 0.0f;

    if (m_moveForward) m_camera->Move(OGL::CameraMovement::FORWARD, window.GetDeltaTime(), speedModifier);
    if (m_moveBackward) m_camera->Move(OGL::CameraMovement::BACKWARD, window.GetDeltaTime(), speedModifier);
    if (m_strafeRight) m_camera->Move(OGL::CameraMovement::RIGHT, window.GetDeltaTime(), speedModifier);
    if (m_strafeLeft) m_camera->Move(OGL::CameraMovement::LEFT, window.GetDeltaTime(), speedModifier);
    if (m_ascend) m_camera->Move(OGL::CameraMovement::UP, window.GetDeltaTime(), speedModifier);
    if (m_descend) m_camera->Move(OGL::CameraMovement::DOWN, window.GetDeltaTime(), speedModifier);
}
