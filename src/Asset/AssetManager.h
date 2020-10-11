#pragma once

#include <map>
#include <memory>
#include "ImageRepository.h"

namespace OGL::Asset
{
    class AssetManager
    {
    public:
        AssetManager();

        [[nodiscard]] std::shared_ptr<Image> GetImage(std::string path) const;

        void UnloadImage(const std::string &path) const;

    private:
        std::unique_ptr<ImageRepository> m_images;
    };
}
