#pragma once

namespace OGL
{
    class Window;

    class WindowEvent
    {
    public:
        explicit WindowEvent(const Window&);

        const Window& GetWindow();

    private:
        const Window& m_window;
    };
}
