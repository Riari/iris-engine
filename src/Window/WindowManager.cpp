#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "Window/WindowManager.hpp"

using namespace OGL;

WindowManager& WindowManager::GetInstance()
{
    static WindowManager instance;
    return instance;
}

Window& WindowManager::Create(const char *id, int width, int height)
{
    auto window = std::make_unique<Window>(id, width, height);
    m_windows.insert(std::pair<const char*, std::unique_ptr<Window>>(id, std::move(window)));
    return Get(id);
}

Window& WindowManager::Get(const char *id)
{
    return *m_windows[id];
}

void WindowManager::Destroy(const char *id)
{
    auto *pWindow = m_windows[id].release();
    delete pWindow;
    m_windows.erase(id);
}
