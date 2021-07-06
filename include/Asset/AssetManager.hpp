#pragma once

#include <map>
#include <memory>

#include "ImageRepository.hpp"
#include "GL/Texture.hpp"
#include "ShaderProgramRepository.hpp"

namespace Iris
{
    class AssetManager
    {
    public:
        AssetManager(AssetManager const&) = delete;
        void operator=(AssetManager const&) = delete;

        static AssetManager& GetInstance()
        {
            static AssetManager instance;
            return instance;
        }

        [[nodiscard]] std::shared_ptr<ShaderProgram> GetShaderProgram(std::string name) const;
        void UnloadShaderProgram(const std::string &name) const;

        [[nodiscard]] std::shared_ptr<Image> GetImage(std::string path) const;
        void UnloadImage(const std::string &path) const;

        [[nodiscard]] std::shared_ptr<Texture> GenerateTexture(std::string path) const;

    private:
        AssetManager() : m_images(new ImageRepository), m_shaderPrograms(new ShaderProgramRepository) {}

        std::unique_ptr<ImageRepository> m_images;
        std::unique_ptr<ShaderProgramRepository> m_shaderPrograms;
    };
}
