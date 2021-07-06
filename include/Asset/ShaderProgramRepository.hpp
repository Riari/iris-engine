#pragma once

#include "AssetRepository.hpp"
#include "GL/Shader/ShaderProgram.hpp"

namespace Iris
{
    class ShaderProgramRepository : public AssetRepository<ShaderProgram>
    {
    public:
        void Unload(const std::string &path);

    private:
        std::shared_ptr<ShaderProgram> Load(std::string path) override;
    };
}
