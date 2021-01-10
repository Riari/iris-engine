#include <string>

#include <stb_image.h>

#include <Asset/Image.hpp>

namespace OGL::Asset
{
    Image::Image(std::string path, unsigned char *data, int width, int height, int channels) :
            m_path(std::move(path)),
            m_data(data),
            m_width(width),
            m_height(height),
            m_channels(channels)
    {}

    Image::~Image()
    {
        stbi_image_free(m_data);
    }

    std::string Image::GetPath() const
    {
        return m_path;
    }

    unsigned char *Image::GetData() const
    {
        return m_data;
    }

    int Image::GetWidth() const
    {
        return m_width;
    }

    int Image::GetHeight() const
    {
        return m_height;
    }

    int Image::GetChannels() const
    {
        return m_channels;
    }
}
