#include <sstream>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "Exception/Exception.hpp"
#include "Input/InputManager.hpp"
#include "Utility/Logger.hpp"
#include "Scene/Scene.hpp"

using namespace OGL;

Window::Window(const int id, const char *title, double fpsCap, int width, int height) :
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

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
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

void Window::Update()
{
    if (m_scene == nullptr) return;

    double now = glfwGetTime();
    m_deltaTime = now - m_lastLoopTime;
    m_fpsTime += m_deltaTime;
    m_updateTime += m_deltaTime;
    m_lastLoopTime = now;

    if (m_fpsTime >= 1.0) {
        std::stringstream title;
        title << m_title << " | " << std::to_string(m_frameCount) << " FPS";
        SetTitle(title.str().c_str());
        m_fpsTime = 0;
        m_frameCount = 0;
    }

    while (m_updateTime >= m_updateFrequency)
    {
        glfwWaitEvents();
        m_scene->Update(*this);
        m_updateTime -= m_updateFrequency;
    }

    if ((m_lastLoopTime - m_lastFrameTime) >= m_frameFrequency)
    {
        m_scene->Render(*this);
        m_frameCount++;
        m_lastFrameTime = m_lastLoopTime;
    }
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

void Window::SetScene(std::shared_ptr<Scene> scene)
{
    m_scene = std::move(scene);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
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

double Window::GetDeltaTime() const
{
    return m_deltaTime;
}
