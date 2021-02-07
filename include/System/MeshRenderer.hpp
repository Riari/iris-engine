#pragma once

#include "System.hpp"

namespace Iris
{
    class MeshRenderer : public System
    {
    public:
        static std::list<ComponentType> GetComponentTypes();

        void SetPointLightId(EntityId);
        void SetActiveCameraId(EntityId);

        void Update(Window&) override;

    private:
        EntityId m_pointLightId;
        EntityId m_activeCameraId;
    };
}