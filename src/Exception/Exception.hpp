#pragma once

#include <string>
#include <exception>

namespace Iris
{
    class Exception : public std::exception
    {
    public:
        explicit Exception(std::string error);

        [[nodiscard]] const char *what() const noexcept override;

    private:
        const std::string m_error;
    };
}
