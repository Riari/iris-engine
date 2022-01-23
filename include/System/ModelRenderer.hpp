#pragma once

#include "System.hpp"

namespace Iris
{
    class ModelRenderer : public System
    {
    public:
        static std::list<ComponentType> GetComponentTypes();

        void SetDirectionalLightId(EntityId);
        void SetActiveCameraId(EntityId);

        void Update(Window&, Scene&, bool debug) override;

    private:
        EntityId m_directionalLightId{};
        EntityId m_activeCameraId{};
    };
}