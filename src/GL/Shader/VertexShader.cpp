#include <utility>

#include <glad/glad.h>

#include "GL/Shader/VertexShader.hpp"

using namespace OGL;

VertexShader::VertexShader(const std::string &name, std::shared_ptr<spdlog::logger> logger) : Shader(
        GL_VERTEX_SHADER, name, "_VS", std::move(logger))
{}
