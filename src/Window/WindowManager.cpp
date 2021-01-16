#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "Window/WindowManager.hpp"

using namespace OGL;

WindowManager& WindowManager::GetInstance()
{
    static WindowManager instance;
    return instance;
}

Window& WindowManager::Create(const int id, const char *title, int width, int height)
{
    auto window = std::make_unique<Window>(id, title, width, height);
    m_windows.insert(std::pair<int, std::unique_ptr<Window>>(id, std::move(window)));
    return Get(id);
}

Window& WindowManager::Get(const int id)
{
    return *m_windows[id];
}

void WindowManager::Destroy(const int id)
{
    auto *pWindow = m_windows[id].release();
    delete pWindow;
    m_windows.erase(id);
}
