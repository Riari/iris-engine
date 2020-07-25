#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../Exception/Exception.h"
#include "ImageRepository.h"

void ImageRepository::Unload(const std::string& path) {
    m_assets.erase(path);
}

std::shared_ptr<Image> ImageRepository::Load(std::string path) {
    int width, height, channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data) throw Exception("Loading image failed (path: " + path + ")");

    return std::make_shared<Image>(path, data, &width, &height, &channels);
}
