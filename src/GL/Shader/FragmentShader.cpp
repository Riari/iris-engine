#include <utility>
#include "FragmentShader.h"

FragmentShader::FragmentShader(const std::string& name) : Shader(GL_FRAGMENT_SHADER, name, "_FS") {}
