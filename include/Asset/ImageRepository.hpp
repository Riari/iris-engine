#pragma once

#include <Asset/AssetRepository.hpp>
#include <Asset/Image.hpp>

namespace OGL::Asset
{
    class ImageRepository : public AssetRepository<Image>
    {
    public:
        void Unload(const std::string &path);

        static void SetFlipVerticallyOnLoad(bool flag);

    private:
        std::shared_ptr<Image> Load(std::string path) override;
    };
}
