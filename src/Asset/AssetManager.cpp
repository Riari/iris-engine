#include "AssetManager.h"

std::shared_ptr<Image> AssetManager::GetImage(std::string path) {
    return m_images->Get(std::move(path));
}
