#include <sstream>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "../Exception/Exception.h"
#include "../Utility/Logger.h"
#include "Window.h"

namespace OGL::Window
{
    Window::Window(const char *id, int width, int height) : m_id(id)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if !defined(NDEBUG)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

        GLFWwindow *window = glfwCreateWindow(width, height, id, NULL, NULL);
        if (window == NULL)
        {
            glfwTerminate();
            throw Exception::Exception("Failed to create GLFW window");
        }

        m_window = window;
        std::stringstream ss;
        ss << "Window::" << id;
        m_logger = Utility::Logger::Create(ss.str().c_str());

        // Callbacks
        glfwSetWindowUserPointer(window, this);
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) { GetPointer(window)->DispatchMouseButtonEvent(button, action, mods); });
        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) { GetPointer(window)->DispatchCursorPosEvent(x, y); });
        glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y) { GetPointer(window)->DispatchScrollEvent(x, y); });
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { GetPointer(window)->DispatchKeyEvent(key, scancode, action, mods); });

        m_logger->info(fmt::format("{0}x{1} window created", width, height));
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
    }

    Size Window::GetSize()
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return Size { width, height };
    }

    Size Window::GetFramebufferSize()
    {
        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);
        return Size { width, height };
    }

    void Window::MakeCurrent()
    {
        glfwMakeContextCurrent(m_window);
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

    void Window::SetInputMode(int mode, int value)
    {
        glfwSetInputMode(m_window, mode, value);
    }

    void Window::SetTitle(const char *title)
    {
        glfwSetWindowTitle(m_window, title);
    }

    void Window::SetShouldClose(bool state)
    {
        glfwSetWindowShouldClose(m_window, state);
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }

    void Window::DispatchMouseButtonEvent(int button, int action, int mods)
    {

    }

    void Window::DispatchCursorPosEvent(int x, int y)
    {

    }

    void Window::DispatchScrollEvent(int x, int y)
    {

    }

    void Window::DispatchKeyEvent(int key, int scancode, int action, int mods)
    {

    }

    Window* Window::GetPointer(GLFWwindow *window)
    {
        auto *ptr = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

        if (!ptr) throw Exception::Exception("Failed to get pointer for window");

        return ptr;
    }
}