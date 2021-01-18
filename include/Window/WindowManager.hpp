#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace OGL
{
    class Window;

    const int DEFAULT_SCREEN_WIDTH = 800;
    const int DEFAULT_SCREEN_HEIGHT = 600;

    class WindowManager
    {
    public:
        WindowManager(WindowManager const&) = delete;
        void operator=(WindowManager const&) = delete;

        static WindowManager& GetInstance();

        std::map<int, std::shared_ptr<Window>> GetWindows();

        Window& Create(int id, const char *title, double fpsCap, int width = DEFAULT_SCREEN_WIDTH, int height = DEFAULT_SCREEN_HEIGHT);
        Window& Get(int id);
        void Destroy(int id);

        template<typename T>
        static void RegisterHandler(std::function<void(const T&)> handler)
        {
            GetHandlers<T>().push_back(handler);
        }

        static void OnFrameBufferCallback(const Window &window, int w, int h);

    private:
        std::map<int, std::shared_ptr<Window>> m_windows;

        WindowManager() = default;

        template<typename T>
        static std::vector<std::function<void(const T&)>>& GetHandlers()
        {
            static std::vector<std::function<void(const T&)>> handlers;
            return handlers;
        }

        static void DispatchFrameBufferEvent(const Window &window, int w, int h);
    };
}
