#include "Exception/Exception.hpp"
#include "Utility/Logger.hpp"
#include "ShaderProgramRepository.hpp"

using namespace Iris;

void ShaderProgramRepository::Unload(const std::string &path)
{
    m_assets.erase(path);
}

std::shared_ptr<GL::ShaderProgram> ShaderProgramRepository::Load(std::string name)
{
    std::shared_ptr<GL::ShaderProgram> program = std::make_shared<GL::ShaderProgram>(name, Logger::GL);
    program->Build();

    return std::move(program);
}
