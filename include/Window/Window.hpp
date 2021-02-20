#pragma once

#include <memory>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace Iris
{
    class Scene;

    class Window
    {
    public:
        Window(int id, const char *title, GLFWmonitor* monitor, int width, int height, double fpsCap);
        ~Window();

        [[nodiscard]] int GetID() const;

        int* GetSize();
        int* GetFramebufferSize();
        float GetAspectRatio();

        [[nodiscard]] double GetDeltaTime() const;
        [[nodiscard]] double GetLastLoopTime() const;

        void MakeCurrent();
        void EnableVsync();
        void Update();
        void SwapBuffers();

        void SetInputMode(int mode, int value);
        void SetTitle(const char* title);
        void SetShouldClose(bool);

        void SetScene(std::shared_ptr<Scene> scene);

        bool ShouldClose();

        void DispatchFrameBufferEvent(int w, int h) const;
        void DispatchMouseButtonEvent(int button, int action, int mods) const;
        void DispatchCursorPosEvent(double x, double y) const;
        void DispatchScrollEvent(double x, double y) const;
        void DispatchKeyEvent(int key, int scancode, int action, int mods) const;

    private:
        const int m_id;
        const char *m_title;
        GLFWwindow *m_window;
        std::shared_ptr<spdlog::logger> m_logger;

        std::shared_ptr<Scene> m_scene;

        double m_updateFrequency;
        double m_frameFrequency;
        double m_deltaTime = 0;
        double m_updateTime = 0;
        double m_lastFrameTime = 0;
        double m_lastLoopTime = 0;
        double m_fpsTime = 0;
        int m_frameCount = 0;

        static Window* GetPointer(GLFWwindow *window);
    };
}