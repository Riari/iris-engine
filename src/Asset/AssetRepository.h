#pragma once

#include <string>
#include <map>
#include <memory>

template<typename T>
class AssetRepository
{
public:
    std::shared_ptr<T> Get(std::string path)
    {
        if (m_assets.find(path) != m_assets.end()) return m_assets[path];

        std::shared_ptr<T> instance = Load(path);
        m_assets[path] = instance;

        return instance;
    };
protected:
    std::map<std::string, std::shared_ptr<T>> m_assets;
private:
    virtual std::shared_ptr<T> Load(std::string path) = 0;
};
