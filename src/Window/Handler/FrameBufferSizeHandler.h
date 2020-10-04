#pragma once

class FrameBufferSizeHandler
{
public:
    virtual void OnFrameBufferSizeCallback(int width, int height) = 0;
};