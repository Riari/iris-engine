#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace Iris
{
    class Window;

    class WindowManager
    {
    public:
        WindowManager(WindowManager const&) = delete;
        void operator=(WindowManager const&) = delete;

        static WindowManager& GetInstance();

        std::map<int, std::shared_ptr<Window>> GetWindows();

        Window& Create(int id, const char *title, int monitor, int width, int height, double fpsCap, GLFWwindow *share = NULL);
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

        static GLFWmonitor* GetMonitor(int monitor);
    };
}
