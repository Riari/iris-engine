#pragma once

#include <map>
#include <string>

#include "Window.hpp"

namespace OGL
{
    const int DEFAULT_SCREEN_WIDTH = 800;
    const int DEFAULT_SCREEN_HEIGHT = 600;

    class WindowManager
    {
    public:
        WindowManager(WindowManager const&) = delete;
        void operator=(WindowManager const&) = delete;

        static WindowManager& GetInstance();

        Window& Create(const char *id, int width = DEFAULT_SCREEN_WIDTH, int height = DEFAULT_SCREEN_HEIGHT);
        Window& Get(const char *id);
        void Destroy(const char *id);

    private:
        std::map<const char*, std::unique_ptr<Window>> m_windows;

        WindowManager() = default;
    };
}
