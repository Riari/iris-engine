#include <utility>
#include "VertexShader.h"

VertexShader::VertexShader(const std::string &name, std::shared_ptr<spdlog::logger> logger) : Shader(GL_VERTEX_SHADER, name, "_VS", std::move(logger))
{}
