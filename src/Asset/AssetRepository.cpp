#include "AssetRepository.h"

template<typename T>
std::shared_ptr<T> AssetRepository<T>::Get(std::string path) const {
    if (m_assets.find(path) != m_assets.end()) return m_assets[path];

    std::shared_ptr<T> instance = Load(path);
    m_assets[path] = instance;

    return instance;
}
