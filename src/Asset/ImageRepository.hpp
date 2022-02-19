#pragma once

#include "AssetRepository.hpp"
#include "Image.hpp"

namespace Iris
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
