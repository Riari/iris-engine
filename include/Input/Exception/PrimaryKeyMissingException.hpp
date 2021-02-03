#pragma once

#include <utility>

#include "Exception/Exception.hpp"

namespace Iris
{
    class PrimaryKeyMissingException : public ::Iris::Exception::Exception
    {
    public:
        explicit PrimaryKeyMissingException() : ::Iris::Exception::Exception("Primary key is required.")
        {}
    };
}
