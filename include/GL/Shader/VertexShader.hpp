#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include "Shader.hpp"

namespace OGL::GL
{
    class VertexShader : public Shader
    {
    public:
        explicit VertexShader(const std::string &name, std::shared_ptr<spdlog::logger> logger);
    };
}
