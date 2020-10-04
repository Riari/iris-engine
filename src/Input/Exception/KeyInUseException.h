#pragma once

#include <utility>

#include "../../Exception/Exception.h"

class KeyInUseException : public Exception
{
public:
    explicit KeyInUseException(std::string error) : Exception(std::move(error))
    {}
};