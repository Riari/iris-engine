#pragma once

#include <string>

#include "Handler/CursorPosHandler.h"
#include "Handler/FrameBufferSizeHandler.h"
#include "Handler/KeyHandler.h"
#include "Handler/ScrollHandler.h"

namespace OGL::Window
{
    const int DEFAULT_SCREEN_WIDTH = 800;
    const int DEFAULT_SCREEN_HEIGHT = 600;

    class Window
    {
    public:
        explicit Window(const char *title, std::shared_ptr<spdlog::logger> logger, int screenWidth = DEFAULT_SCREEN_WIDTH, int screenHeight = DEFAULT_SCREEN_HEIGHT);
        ~Window();

        static void ErrorCallback(int error, const char *message);

        GLFWwindow* GetGLFWWindow();

        [[nodiscard]] int GetScreenWidth() const;
        [[nodiscard]] int GetScreenHeight() const;

        void SetTitle(const char *title);

    private:
        GLFWwindow *m_window;

        int m_screenWidth, m_screenHeight;

        std::shared_ptr<spdlog::logger> m_logger;

        static Window* GetWindowPointer(GLFWwindow *window);
        static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
        static void CursorPosCallback(GLFWwindow *window, double x, double y);
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void ScrollCallback(GLFWwindow *window, double x, double y);

        void OnFrameBufferSizeCallback(int width, int height);
        void OnCursorPosCallback(double x, double y);
        void OnKeyCallback(int key, int scancode, int action, int mods);
        void OnScrollCallback(double x, double y);
    };
}
