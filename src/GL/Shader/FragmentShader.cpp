#include <utility>

#include "FragmentShader.h"

FragmentShader::FragmentShader(const std::string &name, std::shared_ptr<spdlog::logger> logger) : Shader(GL_FRAGMENT_SHADER, name, "_FS", std::move(logger))
{}
