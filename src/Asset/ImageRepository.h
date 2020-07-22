#pragma once

#include "AssetRepository.h"
#include "Image.h"

class ImageRepository : public AssetRepository<Image> {
private:
    std::shared_ptr<Image> Load(std::string path) override;
};