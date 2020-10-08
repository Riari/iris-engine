#pragma once

#include <string>

#include "Handler/CursorPosHandler.h"
#include "Handler/FrameBufferSizeHandler.h"
#include "Handler/KeyHandler.h"
#include "Handler/ScrollHandler.h"

const int DEFAULT_SCREEN_WIDTH = 800;
const int DEFAULT_SCREEN_HEIGHT = 600;

class Window
{
public:
    explicit Window(const char *title, int screenWidth = DEFAULT_SCREEN_WIDTH, int screenHeight = DEFAULT_SCREEN_HEIGHT);
    ~Window();

    static void ErrorCallback(int error, const char *message);

    GLFWwindow* GetGLFWWindow();

    int GetScreenWidth() const;
    int GetScreenHeight() const;

    void RegisterFrameBufferSizeHandler(FrameBufferSizeHandler *handler);
    void RegisterCursorPosHandler(CursorPosHandler *handler);
    void RegisterKeyHandler(KeyHandler *handler);
    void RegisterScrollHandler(ScrollHandler *handler);

private:
    GLFWwindow *m_window;

    int m_screenWidth, m_screenHeight;

    std::vector<FrameBufferSizeHandler*> m_frameBufferSizeHandlers;
    std::vector<CursorPosHandler*> m_cursorPosHandlers;
    std::vector<KeyHandler*> m_keyHandlers;
    std::vector<ScrollHandler*> m_scrollHandlers;

    static Window* GetWindowPointer(GLFWwindow *window);
    static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
    static void CursorPosCallback(GLFWwindow *window, double x, double y);
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void ScrollCallback(GLFWwindow *window, double x, double y);

    void OnFrameBufferSizeCallback(int width, int height);
    void OnCursorPosCallback(double x, double y);
    void OnKeyCallback(int key, int scancode, int action, int mods);
    void OnScrollCallback(double x, double y);
};


