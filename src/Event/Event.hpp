#pragma once

#include <typeindex>

namespace Iris
{
    class Event
    {
    public:
        explicit Event();
        [[nodiscard]] float GetTimestamp() const;

    private:
        const float m_timestamp;
    };
}