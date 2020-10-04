#pragma once

#include <memory>

#include "../GL/Camera.h"
#include "../Utility/Timer.h"
#include "../Input/InputManager.h"
#include "../Window/Handler/CursorPosHandler.h"
#include "../Window/Handler/KeyHandler.h"
#include "../Window/Handler/ScrollHandler.h"

class CameraController : public CursorPosHandler, public ScrollHandler
{
public:
    explicit CameraController(std::shared_ptr<Camera> camera, std::shared_ptr<InputManager> input);

    void OnCursorPosCallback(double x, double y) override;
    void OnScrollCallback(double x, double y) override;

    void Update(float deltaTime);

private:
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<InputManager> m_input;

    bool m_firstCursorPosCallback = true;
    float m_rotateX, m_rotateY, m_lastCursorX, m_lastCursorY;
};
