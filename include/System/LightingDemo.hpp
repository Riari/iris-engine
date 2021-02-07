#pragma once

#include "System.hpp"

namespace Iris
{
    // Temporary system
    class LightingDemo : public System
    {
    public:
        static std::list<ComponentType> GetComponentTypes();
        void Update(Window&) override;
    };
}