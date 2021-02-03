#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include "Shader.hpp"

namespace Iris
{
    class FragmentShader : public Shader
    {
    public:
        explicit FragmentShader(const std::string &name, std::shared_ptr<spdlog::logger> logger);
    };
}
