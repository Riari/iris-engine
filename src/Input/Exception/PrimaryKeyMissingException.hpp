#pragma once

#include <utility>
#include "Exception/Exception.hpp"

namespace Iris
{
    class PrimaryKeyMissingException : public Exception
    {
    public:
        explicit PrimaryKeyMissingException() : Exception("Primary key is required.")
        {}
    };
}
