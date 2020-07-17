#include <utility>
#include "VertexShader.h"

VertexShader::VertexShader(const std::string& name) : Shader(GL_VERTEX_SHADER, name, "_VS") {}
