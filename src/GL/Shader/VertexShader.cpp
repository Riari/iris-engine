#include <utility>
#include "VertexShader.h"

namespace OGL::GL
{
    VertexShader::VertexShader(const std::string &name, std::shared_ptr<spdlog::logger> logger) : Shader(
            GL_VERTEX_SHADER, name, "_VS", std::move(logger))
    {}
}
