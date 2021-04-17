#pragma once

#include <set>

#include <glm/glm.hpp>

#include "Entity/Entity.hpp"
#include "Window/Window.hpp"

namespace Iris
{
    class Scene
    {
    public:
        explicit Scene(int id);

        void SetClearColor(glm::vec4);
        glm::vec4 GetClearColor();

        void AddEntity(EntityId);
        std::set<EntityId> GetEntities();
        void RemoveEntity(EntityId);

    private:
        int m_id;
        glm::vec4 m_clearColor;
        std::set<EntityId> m_entityIds;
    };
}