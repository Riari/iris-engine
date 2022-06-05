#pragma once

#include "AssetRepository.hpp"
#include "GL/Shader/ShaderProgram.hpp"

namespace Iris
{
    class ShaderProgramRepository : public AssetRepository<GL::ShaderProgram>
    {
    public:
        void Unload(const std::string &path);

    private:
        std::shared_ptr<GL::ShaderProgram> Load(std::string path) override;
    };
}
