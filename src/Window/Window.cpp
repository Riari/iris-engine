#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "../Event/EventBus.h"
#include "../Event/WindowResizedEvent.h"
#include "../Exception/Exception.h"
#include "../Utility/Logger.h"
#include "Window.h"

using namespace OGL;
using namespace OGL::Event;

namespace OGL::Window
{
    Window::Window(const char *title, std::shared_ptr<spdlog::logger> logger, int screenWidth, int screenHeight) :
            m_logger(std::move(logger)),
            m_screenWidth(screenWidth),
            m_screenHeight(screenHeight)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if !defined(NDEBUG)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        glfwSetErrorCallback(ErrorCallback);
#endif

        GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
        if (window == NULL)
        {
            glfwTerminate();
            throw Exception::Exception("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        m_window = window;

        // Callbacks
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetScrollCallback(window, ScrollCallback);
        glfwSetKeyCallback(window, KeyCallback);

        m_logger->info(fmt::format("{0}x{1} window created", m_screenWidth, m_screenHeight));
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
    }

    void Window::ErrorCallback(int error, const char *message)
    {
        Utility::Logger::GL->error(message);
    }

    GLFWwindow *Window::GetGLFWWindow()
    {
        return m_window;
    }

    int Window::GetScreenWidth() const
    {
        return m_screenWidth;
    }

    int Window::GetScreenHeight() const
    {
        return m_screenHeight;
    }

    void Window::SetTitle(const char *title)
    {
        glfwSetWindowTitle(m_window, title);
    }

    void Window::FrameBufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        GetWindowPointer(window)->OnFrameBufferSizeCallback(width, height);
    }

    void Window::CursorPosCallback(GLFWwindow *window, double x, double y)
    {
        GetWindowPointer(window)->OnCursorPosCallback(x, y);
    }

    void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        GetWindowPointer(window)->OnKeyCallback(key, scancode, action, mods);
    }

    void Window::ScrollCallback(GLFWwindow *window, double x, double y)
    {
        GetWindowPointer(window)->OnScrollCallback(x, y);
    }

    void Window::OnFrameBufferSizeCallback(int width, int height)
    {
        glViewport(0, 0, width, height);
        m_screenWidth = width;
        m_screenHeight = height;

        EventBus::Dispatch<WindowResizedEvent>(WindowResizedEvent());
    }

    void Window::OnCursorPosCallback(double x, double y)
    {
        // EventBus::Push(std::make_shared<MouseMoveEvent>(x, y));
    }

    void Window::OnKeyCallback(int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(m_window, true);

        // EventBus::Push(std::make_shared<KeyPressEvent>());
    }

    void Window::OnScrollCallback(double x, double y)
    {
        // EventBus::Push(std::make_shared<MouseScrollEvent>());
    }

    Window *Window::GetWindowPointer(GLFWwindow *window)
    {
        auto *handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

        if (!handler) throw Exception::Exception("Failed to get handler for window");

        return handler;
    }
}
