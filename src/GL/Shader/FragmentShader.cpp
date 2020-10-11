#include <utility>

#include "FragmentShader.h"

namespace OGL::GL
{
    FragmentShader::FragmentShader(const std::string &name, std::shared_ptr<spdlog::logger> logger) : Shader(
            GL_FRAGMENT_SHADER, name, "_FS", std::move(logger))
    {}
}