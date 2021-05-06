#pragma once

#include <map>
#include <memory>

#include "ImageRepository.hpp"

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

        [[nodiscard]] std::shared_ptr<Image> GetImage(std::string path) const;

        void UnloadImage(const std::string &path) const;

    private:
        AssetManager() : m_images(new ImageRepository) {}

        std::unique_ptr<ImageRepository> m_images;
    };
}
