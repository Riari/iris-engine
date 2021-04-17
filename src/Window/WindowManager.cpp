#include "Window/Exception/MonitorNotFoundException.hpp"
#include "Window/FrameBufferEvent.hpp"
#include "Window/Window.hpp"
#include "Window/WindowManager.hpp"

using namespace Iris;

WindowManager& WindowManager::GetInstance()
{
    static WindowManager instance;
    return instance;
}

std::map<int, std::shared_ptr<Window>> WindowManager::GetWindows()
{
    return m_windows;
}

Window& WindowManager::Create(const int id, const char *title, int monitor, int width, int height, double fpsCap, GLFWwindow *share)
{
    auto window = std::make_unique<Window>(id, title, GetMonitor(monitor), width, height, fpsCap, share);
    m_windows.insert(std::pair<int, std::shared_ptr<Window>>(id, std::move(window)));
    return Get(id);
}

Window& WindowManager::Get(const int id)
{
    return *m_windows[id];
}

void WindowManager::Destroy(const int id)
{
    m_windows.erase(id);
}

void WindowManager::OnFrameBufferCallback(const Window &window, int w, int h)
{
    DispatchFrameBufferEvent(window, w, h);
}

void WindowManager::DispatchFrameBufferEvent(const Window &window, int w, int h)
{
    auto handlers = GetHandlers<FrameBufferEvent>();
    if (handlers.empty()) return;

    for (const auto& handler : handlers)
    {
        handler(FrameBufferEvent(window, w, h));
    }
}

GLFWmonitor *WindowManager::GetMonitor(int monitor)
{
    if (monitor < 0) return NULL;

    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    if (monitor > count) throw MonitorNotFoundException(monitor, count);

    return monitors[monitor];
}
