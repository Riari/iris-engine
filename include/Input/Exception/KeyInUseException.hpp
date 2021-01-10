#pragma once

#include <utility>

#include "Exception/Exception.hpp"

namespace OGL::Input::Exception
{
    class KeyInUseException : public ::OGL::Exception::Exception
    {
    public:
        explicit KeyInUseException(std::string error) : ::OGL::Exception::Exception(std::move(error))
        {}
    };
}
