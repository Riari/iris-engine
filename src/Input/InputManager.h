#pragma once

#include <map>

#include "InputBinding.h"
#include "../Window/Handler/KeyHandler.h"

class InputManager : public KeyHandler
{
public:
    InputManager();

    InputBinding *MoveForward;
    InputBinding *MoveBackward;
    InputBinding *StrafeLeft;
    InputBinding *StrafeRight;
    InputBinding *GoUp;
    InputBinding *GoDown;

    void OnKeyCallback(int key, int scancode, int action, int mods) override;
    void OnKeybindChange(InputBinding *targetBinding, int key, bool isPrimary = true);

    bool IsPressed(InputBinding *binding);
    bool IsHeld(InputBinding *binding);
    bool IsReleased(InputBinding *binding);

    [[nodiscard]] bool IsCtrlHeld() const;
    [[nodiscard]] bool IsAltHeld() const;
    [[nodiscard]] bool IsShiftHeld() const;

private:
    std::vector<InputBinding*> m_bindings;
    std::vector<int> m_keysPressed;
    std::vector<int> m_keysReleased;
    std::vector<int> m_keysHeld;

    bool m_isCtrlHeld = false;
    bool m_isShiftHeld = false;
    bool m_isAltHeld = false;

    void Setup();
};


