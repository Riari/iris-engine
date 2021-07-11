#include "Demo/Keys.hpp"
#include "Entity/Component/Camera.hpp"
#include "System/CameraController.hpp"

using namespace Iris;

std::list<ComponentType> CameraController::GetComponentTypes()
{
    return {};
}

void CameraController::SetActiveCameraId(EntityId id)
{
    m_activeCameraId = id;
    UpdateVectors();
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
    AdjustFOV(event.GetY());
}

void CameraController::AdjustFOV(float adjustment) const
{
    auto& camera = GetComponent<Camera>(m_activeCameraId);

    camera.fov -= adjustment;

    if (camera.fov < 1.0f) camera.fov = 1.0f;
    if (camera.fov > DEFAULT_FOV) camera.fov = DEFAULT_FOV;
}

void CameraController::Move(CameraMovement direction, double deltaTime, double moveSpeed) const
{
    auto& camera = GetComponent<Camera>(m_activeCameraId);

    float velocity = moveSpeed * deltaTime;

    switch (direction)
    {
        case CameraMovement::FORWARD:
            camera.position += camera.front * velocity;
            break;
        case CameraMovement::BACKWARD:
            camera.position -= camera.front * velocity;
            break;
        case CameraMovement::LEFT:
            camera.position -= camera.right * velocity;
            break;
        case CameraMovement::RIGHT:
            camera.position += camera.right * velocity;
            break;
        case CameraMovement::UP:
            camera.position += camera.up * velocity;
            break;
        case CameraMovement::DOWN:
            camera.position -= camera.up * velocity;
            break;
    }
}

void CameraController::Rotate(float xOffset, float yOffset, double deltaTime, double rotateSpeed) const
{
    auto& camera = GetComponent<Camera>(m_activeCameraId);

    float velocity = rotateSpeed * deltaTime;

    camera.yaw = glm::mod(camera.yaw + (xOffset * velocity), 360.0f);
    camera.pitch += yOffset * velocity;

    if (camera.constrainPitch)
    {
        if (camera.pitch > 89.0f) camera.pitch = 89.0f;
        if (camera.pitch < -89.0f) camera.pitch = -89.0f;
    }

    UpdateVectors();
}

void CameraController::UpdateVectors() const
{
    auto& camera = GetComponent<Camera>(m_activeCameraId);

    glm::vec3 front;
    front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    front.y = sin(glm::radians(camera.pitch));
    front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));

    camera.front = glm::normalize(front);
    camera.right = glm::normalize(glm::cross(front, camera.worldUp));
    camera.up = glm::normalize(glm::cross(camera.right, front));
}

void CameraController::Update(Window& window, bool debug)
{
    window.SetInputMode(GLFW_CURSOR, debug ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED );

    if (debug) return;

    auto deltaTime = window.GetDeltaTime();

    Rotate(m_rotateX, m_rotateY, deltaTime, 1.0f);
    m_rotateX = 0.0f;
    m_rotateY = 0.0f;

    float moveSpeed = Iris::InputManager::IsAltDown() ? 5.0f : 1.0f;

    if (m_moveForward) Move(CameraMovement::FORWARD, deltaTime, moveSpeed);
    if (m_moveBackward) Move(CameraMovement::BACKWARD, deltaTime, moveSpeed);
    if (m_strafeRight) Move(CameraMovement::RIGHT, deltaTime, moveSpeed);
    if (m_strafeLeft) Move(CameraMovement::LEFT, deltaTime, moveSpeed);
    if (m_ascend) Move(CameraMovement::UP, deltaTime, moveSpeed);
    if (m_descend) Move(CameraMovement::DOWN, deltaTime, moveSpeed);
}
