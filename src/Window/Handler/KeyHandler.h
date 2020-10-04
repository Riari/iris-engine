#pragma once

class KeyHandler
{
public:
    virtual void OnKeyCallback(int key, int scancode, int action, int mods) = 0;
};