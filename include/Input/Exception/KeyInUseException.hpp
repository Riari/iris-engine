#pragma once

#include <utility>

#include "Exception/Exception.hpp"

namespace Iris
{
    class KeyInUseException : public Exception
    {
    public:
        explicit KeyInUseException(std::string error) : Exception(std::move(error))
        {}
    };
}
