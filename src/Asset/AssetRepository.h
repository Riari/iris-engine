#pragma once

#include <string>
#include <map>
#include <memory>

template <typename T>
class AssetRepository {
public:
    std::shared_ptr<T> Get(std::string path) const;
protected:
    std::map<std::string, T> m_assets;
private:
    virtual std::shared_ptr<T> Load(std::string path) = 0;
};
