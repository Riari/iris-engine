#include "Demo/Keys.hpp"
#include "Entity/Component/Camera.hpp"
#include "System/CameraController.hpp"
#include "System/SystemManager.hpp"

using namespace Iris;

std::list<ComponentType> CameraController::GetComponentTypes()
{
    return {};
}

void CameraController::SetActiveCameraId(EntityId id)
{
    m_activeCameraId = id;
}

void CameraController::Handle(FrameBufferEvent event)
{
    GetComponent<Camera>(m_activeCameraId).aspectRatio = (float) event.GetWidth() / (float) event.GetHeight();
}

void CameraController::Handle(KeyEvent event)
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

void CameraController::Handle(MouseMoveEvent event)
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

void CameraController::Handle(MouseScrollEvent event)
{
    GetComponent<Camera>(m_activeCameraId).AdjustFOV(event.GetY());
}

void CameraController::Update(Window &window)
{
    auto& camera = GetComponent<Camera>(m_activeCameraId);

    camera.Rotate(m_rotateX, m_rotateY, window.GetDeltaTime(), 1.0f);
    m_rotateX = 0.0f;
    m_rotateY = 0.0f;

    float moveSpeed = Iris::InputManager::IsAltDown() ? 5.0f : 1.0f;

    if (m_moveForward) camera.Move(CameraMovement::FORWARD, window.GetDeltaTime(), moveSpeed);
    if (m_moveBackward) camera.Move(CameraMovement::BACKWARD, window.GetDeltaTime(), moveSpeed);
    if (m_strafeRight) camera.Move(CameraMovement::RIGHT, window.GetDeltaTime(), moveSpeed);
    if (m_strafeLeft) camera.Move(CameraMovement::LEFT, window.GetDeltaTime(), moveSpeed);
    if (m_ascend) camera.Move(CameraMovement::UP, window.GetDeltaTime(), moveSpeed);
    if (m_descend) camera.Move(CameraMovement::DOWN, window.GetDeltaTime(), moveSpeed);
}
