#pragma once

#include "System.hpp"
#include "Input/InputHandler.hpp"
#include "Input/InputManager.hpp"
#include "Input/KeyEvent.hpp"
#include "Window/FrameBufferEvent.hpp"
#include "Window/Window.hpp"
#include "Window/WindowEventHandler.hpp"

namespace Iris
{
    enum class CameraMovement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    class CameraController :
            public System,
            public WindowEventHandler<FrameBufferEvent>,
            public InputHandler<KeyEvent>,
            public InputHandler<MouseMoveEvent>,
            public InputHandler<MouseScrollEvent>
    {
    public:
        static std::list<ComponentType> GetComponentTypes();

        void SetActiveCameraId(EntityId);

        void Handle(FrameBufferEvent) override;
        void Handle(KeyEvent) override;
        void Handle(MouseMoveEvent) override;
        void Handle(MouseScrollEvent) override;

        void AdjustFOV(float adjustment) const;
        void Move(CameraMovement direction, double deltaTime, double moveSpeed) const;
        void Rotate(float xOffset, float yOffset, double deltaTime, double rotateSpeed) const;
        void UpdateVectors() const;

        void Update(Window& window, bool debug) override;

    private:
        EntityId m_activeCameraId;

        bool m_moveForward = false;
        bool m_moveBackward = false;
        bool m_strafeLeft = false;
        bool m_strafeRight = false;
        bool m_ascend = false;
        bool m_descend = false;
        bool m_focused = true;

        bool m_receivedFirstMouseMoveEvent = false;
        float m_rotateX, m_rotateY, m_lastCursorX, m_lastCursorY;
    };
}