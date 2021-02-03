#include <utility>

#include <glad/glad.h>

#include "GL/Shader/FragmentShader.hpp"

using namespace Iris;

FragmentShader::FragmentShader(const std::string &name, std::shared_ptr<spdlog::logger> logger) : Shader(
        GL_FRAGMENT_SHADER, name, "_FS", std::move(logger))
{}
