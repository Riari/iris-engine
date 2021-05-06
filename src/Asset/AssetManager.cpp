#include "Asset/AssetManager.hpp"

using namespace Iris;

std::shared_ptr<Image> AssetManager::GetImage(std::string path) const
{
    return m_images->Get(std::move(path));
}

void AssetManager::UnloadImage(const std::string &path) const
{
    m_images->Unload(path);
}

std::shared_ptr<Texture> AssetManager::GenerateTexture(std::string path) const
{
    std::shared_ptr<Image> image = GetImage(path);
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(image);
    texture->Bind(GL_TEXTURE0);
    texture->Define();
    UnloadImage(image->GetPath());

    return texture;
}
