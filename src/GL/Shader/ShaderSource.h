#pragma once

#include <iostream>
#include <glad\glad.h>

class ShaderSource {
public:
    ShaderSource(std::string name, std::string suffix);
    ~ShaderSource();

    const GLchar* GetSource();
private:
    const std::string m_name;
    const std::string m_suffix{};
    const std::string m_path = "src/GL/Shader/Source/";
    const std::string m_extension = ".glsl";
    const GLchar *m_source{};

    void Load();
};
