#include <GLFW/glfw3.h>

#include "Event/Event.hpp"

using namespace Iris;

Event::Event() : m_timestamp(glfwGetTime()) {}

float Event::GetTimestamp() const
{
    return m_timestamp;
}
