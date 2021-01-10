#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <Event.h>

namespace OGL::Event
{
    class EventBus
    {
    public:
        template<typename T>
        static void Subscribe(std::function<bool(const T&)> listener)
        {
            GetListeners<T>().push_back(std::move(listener));
        }

        template<typename T>
        static void Dispatch(const T& event)
        {
            for (const auto& listener : GetListeners<T>())
            {
                if (listener(event)) break;
            }
        }

    private:
        template<typename T>
        static std::vector<std::function<bool(const T&)>>& GetListeners()
        {
            static std::vector<std::function<bool(const T&)>> listeners;
            return listeners;
        }
    };
}