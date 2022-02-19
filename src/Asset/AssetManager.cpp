#include <utility>
#include "AssetManager.hpp"

using namespace Iris;

std::shared_ptr<ShaderProgram> AssetManager::GetShaderProgram(std::string name) const
{
    return m_shaderPrograms->Get(std::move(name));
}

void AssetManager::UnloadShaderProgram(const std::string &name) const
{
    m_shaderPrograms->Unload(name);
}

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
    std::shared_ptr<Image> image = GetImage(std::move(path));
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(image);
    texture->Bind();
    texture->Define();
    UnloadImage(image->GetPath());

    return texture;
}
