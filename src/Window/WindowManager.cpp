#include "Window/FrameBufferEvent.hpp"
#include "Window/Window.hpp"
#include "Window/WindowManager.hpp"

using namespace OGL;

WindowManager& WindowManager::GetInstance()
{
    static WindowManager instance;
    return instance;
}

std::map<int, std::shared_ptr<Window>> WindowManager::GetWindows()
{
    return m_windows;
}

Window& WindowManager::Create(const int id, const char *title, double fpsCap, int width, int height)
{
    auto window = std::make_unique<Window>(id, title, fpsCap, width, height);
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
