#pragma once

class Image
{
public:
    explicit Image(std::string path, unsigned char *data, int width, int height, int channels);
    ~Image();

    [[nodiscard]] std::string GetPath() const;
    [[nodiscard]] unsigned char *GetData() const;
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] int GetChannels() const;

private:
    std::string m_path;
    unsigned char *m_data{};
    int m_width{};
    int m_height{};
    int m_channels{};
};