#include <utility>
#include "VertexShader.h"

VertexShader::VertexShader(std::string name) : Shader(GL_VERTEX_SHADER, std::move(name), "_VS") {}
