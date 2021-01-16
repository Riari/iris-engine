#pragma once

namespace OGL
{
    class Window;

    class InputEvent
    {
    public:
        explicit InputEvent(const Window&);

        const Window& GetWindow();

    private:
        const Window& m_window;
    };
}