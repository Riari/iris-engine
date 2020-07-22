#include "Image.h"

Image::Image(unsigned char *data, int *width, int *height, int *channels) :
    m_data(data),
    m_width(width),
    m_height(height),
    m_channels(channels) {}
