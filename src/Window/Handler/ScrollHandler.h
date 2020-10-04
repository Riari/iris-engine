#pragma once

class ScrollHandler
{
public:
    virtual void OnScrollCallback(double x, double y) = 0;
};