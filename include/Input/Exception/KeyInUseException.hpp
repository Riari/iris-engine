#pragma once

#include <utility>

#include "Exception/Exception.hpp"

namespace Iris
{
    class KeyInUseException : public ::Iris::Exception::Exception
    {
    public:
        explicit KeyInUseException(std::string error) : ::Iris::Exception::Exception(std::move(error))
        {}
    };
}
