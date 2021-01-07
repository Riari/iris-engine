#include "Event.h"

namespace OGL::Event
{
    Event::Event(float timestamp) : m_timestamp(timestamp) {}

    float Event::GetTimestamp() const
    {
        return m_timestamp;
    }
}