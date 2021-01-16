#pragma once

#include <functional>
#include <map>
#include <vector>

#include "InputBinding.hpp"
#include "KeyEvent.hpp"
#include "MouseButtonEvent.hpp"
#include "MouseMoveEvent.hpp"
#include "MouseScrollEvent.hpp"

namespace OGL
{
    class InputManager
    {
    public:
        static void RegisterBinding(int id, int primaryKey, int secondaryKey = GLFW_KEY_UNKNOWN, bool force = false);

        template<typename T>
        static void RegisterHandler(std::function<void(const T&)> handler)
        {
            GetHandlers<T>().push_back(handler);
        }

        static void OnMouseButtonCallback(const Window &window, int button, int action, int mods);
        static void OnCursorPosCallback(const Window &window, double x, double y);
        static void OnScrollCallback(const Window &window, double x, double y);
        static void OnKeyCallback(const Window &window, int key, int scancode, int action, int mods);

        [[nodiscard]] static bool IsCtrlDown();
        [[nodiscard]] static bool IsShiftDown();
        [[nodiscard]] static bool IsAltDown();
        [[nodiscard]] static bool IsSuperDown();
        [[nodiscard]] static bool IsCapsLockOn();
        [[nodiscard]] static bool IsNumLockOn();

    private:
        InputManager() = default;

        static inline std::map<int, std::shared_ptr<InputBinding>> m_bindings;

        static inline std::vector<int> m_keysPressed;
        static inline std::vector<int> m_keysReleased;

        static inline bool m_isCtrlDown = false;
        static inline bool m_isShiftDown = false;
        static inline bool m_isAltHeld = false;
        static inline bool m_isSuperDown = false;
        static inline bool m_isCapsLockOn = false;
        static inline bool m_isNumLockOn = false;

        template<typename T>
        static std::vector<std::function<void(const T&)>>& GetHandlers()
        {
            static std::vector<std::function<void(const T&)>> handlers;
            return handlers;
        }

        static void ValidateKeyAvailable(int key);

        static void UpdateModifierKeys(int mods);

        static void DispatchMouseButtonEvent(const Window &window, int button, int action);
        static void DispatchMouseMoveEvent(const Window &window, double x, double y);
        static void DispatchMouseScrollEvent(const Window &window, double x, double y);
        static void DispatchKeyEvent(const Window &window, int key, int action);
    };
}
