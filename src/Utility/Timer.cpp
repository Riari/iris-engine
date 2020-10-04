#include <GLFW/glfw3.h>

#include "Timer.h"

Timer::Timer() = default;

void Timer::Tick()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrameTime;
    m_lastFrameTime = currentFrame;
}

float Timer::GetDeltaTime() const
{
    return m_deltaTime;
}