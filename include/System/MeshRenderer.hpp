#pragma once

#include "System.hpp"

namespace Iris
{
    class MeshRenderer : public System
    {
    public:
        MeshRenderer();

        static std::list<ComponentType> GetComponentTypes();

        void SetDirectionalLightId(EntityId);
        void SetPointLightId(EntityId);
        void SetSpotLightId(EntityId);
        void SetActiveCameraId(EntityId);

        void Update(Window&, Scene&) override;

    private:
        EntityId m_directionalLightId{};
        EntityId m_pointLightId{};
        EntityId m_spotLightId{};
        EntityId m_activeCameraId{};

        std::unique_ptr<ShaderProgram> m_pBasicShaderProgram;
        std::unique_ptr<ShaderProgram> m_pMatShaderProg;
    };
}