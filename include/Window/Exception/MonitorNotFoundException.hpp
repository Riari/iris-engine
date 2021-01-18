#pragma once

#include <utility>

#include <spdlog/spdlog.h>

#include "Exception/Exception.hpp"

namespace OGL
{
    class MonitorNotFoundException : public Exception
    {
    public:
        explicit MonitorNotFoundException(int monitor, int availableMonitors) :
            Exception(fmt::format("Tried to select monitor {0} but only {1} monitors available.", monitor, availableMonitors))
        {}
    };
}
