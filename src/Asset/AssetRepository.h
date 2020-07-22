#pragma once

#include <string>
#include <map>
#include <memory>

template <typename T>
class AssetRepository {
public:
    std::shared_ptr<T> Get(std::string path);
private:
    std::map<std::string, T> m_assets;

    virtual std::shared_ptr<T> Load(std::string path) = 0;
};
