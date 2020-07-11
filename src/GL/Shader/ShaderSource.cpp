#include <utility>
#include <fstream>
#include "ShaderSource.h"
#include "../../Exception/Exception.h"

ShaderSource::ShaderSource(std::string name, std::string suffix) : m_name(std::move(name)), m_suffix(std::move(suffix)) {
    Load();
}

void ShaderSource::Load() {
    std::string content;
    std::string filepath = m_path + m_name + m_suffix + m_extension;
    std::ifstream fileStream(filepath.c_str(), std::ios::in);

    if (!fileStream.is_open()) throw Exception("Failed to open " + filepath);

    std::string line;
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    m_source = content.c_str();
}

ShaderSource::~ShaderSource() {
    delete[] m_source;
}

const GLchar* ShaderSource::GetSource() {
    return m_source;
}
