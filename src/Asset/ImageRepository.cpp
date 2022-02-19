#define STB_IMAGE_IMPLEMENTATION

#include <fmt/core.h>
#include <stb_image.h>
#include "Exception/Exception.hpp"
#include "Asset/ImageRepository.hpp"

using namespace Iris;

void ImageRepository::Unload(const std::string &path)
{
    m_assets.erase(path);
}

void ImageRepository::SetFlipVerticallyOnLoad(bool flag)
{
    stbi_set_flip_vertically_on_load(flag);
}

std::shared_ptr<Image> ImageRepository::Load(std::string path)
{
    int width, height, channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data) throw Exception(fmt::format("Loading image failed (path: {0})", path));

    return std::make_shared<Image>(path, data, width, height, channels);
}
