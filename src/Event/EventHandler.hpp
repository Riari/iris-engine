#pragma once

#include "EventBus.hpp"

namespace Iris
{
    template<typename T>
    class EventHandler
    {
    public:
        EventHandler()
        {
            EventBus::Subscribe<T>([this](const T& event) -> bool { return Handle(event); });
        }

    private:
        virtual bool Handle(const T&) = 0;
    };
}