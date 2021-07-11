#pragma once

#include <memory>

#include "GL/Shader/ShaderProgram.hpp"
#include "System.hpp"

namespace Iris
{
    class SpotLightController : public System
    {
    public:
        static std::list<ComponentType> GetComponentTypes();

        void Update(Window&, Scene&, bool debug) override;

        void SetCameraId(EntityId);

    private:
        EntityId m_cameraId{};
    };
}