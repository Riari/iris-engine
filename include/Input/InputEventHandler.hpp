#pragma once

namespace OGL
{
    class Window;

    class InputEventHandler
    {
    public:
        explicit InputEventHandler(const Window&);

        const Window& GetWindow();

    private:
        const Window& m_window;
    };
}
