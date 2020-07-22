#pragma once

class Image {
public:
    explicit Image(unsigned char *data, int *width, int *height, int *channels);

private:
    unsigned char *m_data{};
    int *m_width{};
    int *m_height{};
    int *m_channels{};
};