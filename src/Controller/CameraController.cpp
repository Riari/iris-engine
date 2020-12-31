#include "CameraController.h"

namespace OGL::Controller
{
    CameraController::CameraController(std::shared_ptr<OGL::GL::Camera> camera, std::shared_ptr<OGL::Input::InputManager> input) :
            m_camera(std::move(camera)),
            m_input(std::move(input))
    {}

    void CameraController::OnCursorPosCallback(double x, double y)
    {
        if (m_firstCursorPosCallback)
        {
            m_lastCursorX = x;
            m_lastCursorY = y;
            m_firstCursorPosCallback = false;
        }

        m_rotateX += x - m_lastCursorX;
        m_rotateY += m_lastCursorY - y;

        m_lastCursorX = x;
        m_lastCursorY = y;
    }

    void CameraController::OnScrollCallback(double x, double y)
    {
        m_camera->AdjustFOV(y);
    }

    void CameraController::Update(double deltaTime)
    {
        m_camera->Rotate(m_rotateX, m_rotateY, deltaTime);
        m_rotateX = 0.0f;
        m_rotateY = 0.0f;

        float speedModifier = m_input->IsShiftHeld() ? 4.0f : 0.0f;

        if (m_input->IsHeld(m_input->MoveForward)) m_camera->Move(OGL::GL::CameraMovement::FORWARD, deltaTime, speedModifier);
        if (m_input->IsHeld(m_input->MoveBackward)) m_camera->Move(OGL::GL::CameraMovement::BACKWARD, deltaTime, speedModifier);
        if (m_input->IsHeld(m_input->StrafeLeft)) m_camera->Move(OGL::GL::CameraMovement::LEFT, deltaTime, speedModifier);
        if (m_input->IsHeld(m_input->StrafeRight)) m_camera->Move(OGL::GL::CameraMovement::RIGHT, deltaTime, speedModifier);
        if (m_input->IsHeld(m_input->GoUp)) m_camera->Move(OGL::GL::CameraMovement::UP, deltaTime, speedModifier);
        if (m_input->IsHeld(m_input->GoDown)) m_camera->Move(OGL::GL::CameraMovement::DOWN, deltaTime, speedModifier);
    }
}
