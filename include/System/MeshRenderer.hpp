#pragma once

#include "System.hpp"

namespace Iris
{
    class MeshRenderer : public System
    {
    public:
        static std::list<ComponentType> GetComponentTypes();

        void SetDirectionalLightId(EntityId);
        void SetActiveCameraId(EntityId);

        void Update(Window&, Scene&) override;

    private:
        EntityId m_directionalLightId{};
        EntityId m_activeCameraId{};
    };
}