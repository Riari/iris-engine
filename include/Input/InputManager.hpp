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

        static void OnKeyCallback(const Window &window, int key, int scancode, int action, int mods);

        [[nodiscard]] static bool IsCtrlHeld();
        [[nodiscard]] static bool IsAltHeld();
        [[nodiscard]] static bool IsShiftHeld();

    private:
        InputManager() = default;

        static inline std::map<int, std::shared_ptr<InputBinding>> m_bindings;

        static inline std::vector<int> m_keysPressed;
        static inline std::vector<int> m_keysReleased;

        static inline bool m_isCtrlHeld = false;
        static inline bool m_isShiftHeld = false;
        static inline bool m_isAltHeld = false;

        template<typename T>
        static std::vector<std::function<void(const T&)>>& GetHandlers()
        {
            static std::vector<std::function<void(const T&)>> handlers;
            return handlers;
        }

        static void ValidateKeyAvailable(int key);

        static void DispatchKeyEvent(const Window &window, int key, int action);
    };
}
