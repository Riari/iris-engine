#include "SceneManager.hpp"

using namespace Iris;

SceneManager &SceneManager::GetInstance()
{
    static SceneManager instance;
    return instance;
}

Scene &SceneManager::Create(int id)
{
    auto scene = std::make_unique<Scene>(id);
    m_scenes.insert(std::pair<int, std::shared_ptr<Scene>>(id, std::move(scene)));
    return Get(id);
}

Scene &SceneManager::Get(int id)
{
    return *m_scenes[id];
}
