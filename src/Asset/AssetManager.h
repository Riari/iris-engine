#pragma once

#include <map>
#include <memory>
#include "AssetRepository.h"
#include "ImageRepository.h"

class AssetManager {
public:
    std::shared_ptr<Image> GetImage(std::string path);
private:
    std::unique_ptr<ImageRepository> m_images;
};