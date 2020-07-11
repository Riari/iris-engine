#include <utility>
#include "VertexShaderSource.h"

VertexShaderSource::VertexShaderSource(std::string name) : ShaderSource(std::move(name), "_VS") {}
