#include "Asset/ShaderProgramRepository.hpp"
#include "Exception/Exception.hpp"
#include "Utility/Logger.hpp"

using namespace Iris;

void ShaderProgramRepository::Unload(const std::string &path)
{
    m_assets.erase(path);
}

std::shared_ptr<ShaderProgram> ShaderProgramRepository::Load(std::string name)
{
    std::shared_ptr<ShaderProgram> program = std::make_shared<ShaderProgram>(name, Logger::GL);
    program->Build();

    return std::move(program);
}
