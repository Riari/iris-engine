#include <sstream>
#include <utility>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "Demo/Keys.hpp"
#include "Exception/Exception.hpp"
#include "Input/InputManager.hpp"
#include "Utility/Logger.hpp"
#include "Scene/Scene.hpp"
#include "Window.hpp"
#include "WindowManager.hpp"

using namespace Iris;

Window::Window(int id, const char *title, GLFWmonitor* monitor, int width, int height, double fpsCap, GLFWwindow* share) :
    m_id(id),
    m_title(title),
    m_updateFrequency(1.0 / std::max(fpsCap, 120.0)),
    m_frameFrequency(1.0 / fpsCap)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if !defined(NDEBUG)
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
    if (window == NULL)
    {
        glfwTerminate();
        throw Exception("Failed to create GLFW window");
    }

    m_window = window;
    std::stringstream ss;
    ss << "Window::" << id;
    m_logger = Logger::Create(ss.str().c_str());

    // Callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) { GetPointer(window)->DispatchFrameBufferEvent(w, h); });
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

int Window::GetID() const
{
    return m_id;
}

GLFWwindow *Window::GetGLFWWindow()
{
    return m_window;
}

int* Window::GetSize()
{
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    return new int[2] { width, height };
}

int* Window::GetFramebufferSize()
{
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    return new int[2] { width, height };
}

float Window::GetAspectRatio()
{
    auto size = GetFramebufferSize();
    return (float) size[0] / (float) size[1];
}

void Window::MakeCurrent()
{
    glfwMakeContextCurrent(m_window);
}

void Window::EnableVsync()
{
    glfwSwapInterval(1);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
    m_frameCount++;
}

void Window::SetInputMode(int mode, int value)
{
    glfwSetInputMode(m_window, mode, value);
}

void Window::SetTitle(const char *title)
{
    glfwSetWindowTitle(m_window, title);
}

const char *Window::GetTitle()
{
    return m_title;
}

void Window::SetShouldClose(bool state)
{
    glfwSetWindowShouldClose(m_window, state);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::Tick()
{
    double now = glfwGetTime();
    m_deltaTime = now - m_lastLoopTime;
    m_fpsTime += m_deltaTime;
    m_updateTime += m_deltaTime;
    m_lastLoopTime = now;
}

bool Window::ShouldUpdateFPS() const
{
    return m_fpsTime >= 1.0;
}

bool Window::ShouldUpdate() const
{
    return m_updateTime >= m_updateFrequency;
}

void Window::OnUpdated()
{
    m_updateTime -= m_updateFrequency;
}

double Window::GetDeltaTime() const
{
    return m_deltaTime;
}

double Window::GetLastLoopTime() const {
    return m_lastLoopTime;
}

int Window::GetFrameCount() const
{
    return m_frameCount;
}

void Window::ResetFPSState()
{
    m_fpsTime = 0;
    m_frameCount = 0;
}

void Window::DispatchFrameBufferEvent(int w, int h) const
{
    WindowManager::OnFrameBufferCallback(*this, w, h);
}

void Window::DispatchMouseButtonEvent(int button, int action, int mods) const
{
    InputManager::OnMouseButtonCallback(*this, button, action, mods);
}

void Window::DispatchCursorPosEvent(double x, double y) const
{
    InputManager::OnCursorPosCallback(*this, x, y);
}

void Window::DispatchScrollEvent(double x, double y) const
{
    InputManager::OnScrollCallback(*this, x, y);
}

void Window::DispatchKeyEvent(int key, int scancode, int action, int mods) const
{
    InputManager::OnKeyCallback(*this, key, scancode, action, mods);
}

Window* Window::GetPointer(GLFWwindow *window)
{
    auto *ptr = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

    if (!ptr) throw Exception("Failed to get pointer for window");

    return ptr;
}
