#include <utility>
#include "Exception.h"

namespace OGL::Exception
{
    Exception::Exception(std::string error) : m_error(std::move(error))
    {}

    const char *Exception::what() const noexcept
    {
        return m_error.c_str();
    }
}
