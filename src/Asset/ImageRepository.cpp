#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ImageRepository.h"

std::shared_ptr<Image> ImageRepository::Load(std::string path) {
    int width, height, channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    return std::make_shared<Image>(data, &width, &height, &channels);
}
