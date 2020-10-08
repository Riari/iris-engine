#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "../Exception/Exception.h"
#include "Window.h"

Window::Window(const char *title, int screenWidth, int screenHeight) :
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
        throw Exception("Failed to create GLFW window");
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

    spdlog::info("Window: Created");
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
}

void Window::ErrorCallback(int error, const char *message)
{
    spdlog::error(message);
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

void Window::RegisterFrameBufferSizeHandler(FrameBufferSizeHandler *handler)
{
    m_frameBufferSizeHandlers.push_back(handler);
}

void Window::RegisterCursorPosHandler(CursorPosHandler *handler)
{
    m_cursorPosHandlers.push_back(handler);
}

void Window::RegisterKeyHandler(KeyHandler *handler)
{
    m_keyHandlers.push_back(handler);
}

void Window::RegisterScrollHandler(ScrollHandler *handler)
{
    m_scrollHandlers.push_back(handler);
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

    for (auto handler : m_frameBufferSizeHandlers)
    {
        handler->OnFrameBufferSizeCallback(width, height);
    }
}

void Window::OnCursorPosCallback(double x, double y)
{
    for (auto handler : m_cursorPosHandlers)
    {
        handler->OnCursorPosCallback(x, y);
    }
}

void Window::OnKeyCallback(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(m_window, true);

    for (auto handler : m_keyHandlers)
    {
        handler->OnKeyCallback(key, scancode, action, mods);
    }
}

void Window::OnScrollCallback(double x, double y)
{
    for (auto handler : m_scrollHandlers)
    {
        handler->OnScrollCallback(x, y);
    }
}

Window *Window::GetWindowPointer(GLFWwindow *window)
{
    auto *handler = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

    if (!handler) throw Exception("Failed to get handler for window");

    return handler;
}