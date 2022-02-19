#pragma once

#include <map>
#include <memory>
#include "Scene.hpp"

namespace Iris { class SceneManager; }

class Iris::SceneManager
{
public:
    SceneManager(SceneManager const&) = delete;
    void operator=(SceneManager const&) = delete;

    static SceneManager& GetInstance();

    Scene& Create(int id);
    Scene& Get(int id);

private:
    SceneManager() = default;

    std::map<int, std::shared_ptr<Scene>> m_scenes;
};