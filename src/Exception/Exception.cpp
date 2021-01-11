#include <utility>

#include "Exception/Exception.hpp"

using namespace OGL;

Exception::Exception(std::string error) : m_error(std::move(error))
{}

const char *Exception::what() const noexcept
{
    return m_error.c_str();
}
