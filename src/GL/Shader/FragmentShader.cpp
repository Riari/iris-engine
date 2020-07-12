#include <utility>
#include "FragmentShader.h"

FragmentShader::FragmentShader(std::string name) : Shader(GL_FRAGMENT_SHADER, std::move(name), "_FS") {}
