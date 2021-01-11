#pragma once

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <memory>

namespace OGL
{
    class Window
    {
    public:
        Window(const char *id, int width, int height);
        ~Window();

        int* GetSize();
        int* GetFramebufferSize();

        void MakeCurrent();
        void SwapBuffers();

        void SetInputMode(int mode, int value);
        void SetTitle(const char* title);
        void SetShouldClose(bool);

        bool ShouldClose();

        void DispatchMouseButtonEvent(int button, int action, int mods);
        void DispatchCursorPosEvent(int x, int y);
        void DispatchScrollEvent(int x, int y);
        void DispatchKeyEvent(int key, int scancode, int action, int mods);

    private:
        const char *m_id;
        GLFWwindow *m_window;
        std::shared_ptr<spdlog::logger> m_logger;

        static Window* GetPointer(GLFWwindow *window);
    };
}