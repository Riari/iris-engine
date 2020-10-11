#pragma once

namespace OGL::Utility
{
    class Timer
    {
    public:
        Timer();

        void Tick();

        [[nodiscard]] float GetDeltaTime() const;

    private:
        float m_deltaTime = 0.0f, m_lastFrameTime = 0.0f;
    };
}
