#pragma once

#include <typeindex>

namespace OGL
{
    class Event
    {
    public:
        explicit Event(float timestamp = 0.0f);
        [[nodiscard]] float GetTimestamp() const;

    private:
        const float m_timestamp;
    };
}