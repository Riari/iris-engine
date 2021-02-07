#pragma once

#include <memory>

#include "Scene/Scene.hpp"
#include "System/CameraController.hpp"
#include "System/LightingDemo.hpp"
#include "System/MeshRenderer.hpp"

namespace Iris
{
    class MainScene : public Scene
    {
    public:
        void Setup(float aspectRatio) override;
        void Update(Window&) override;
        void Render(Window&) override;
        void Teardown() override;

    private:
        std::shared_ptr<CameraController> m_cameraController;
        std::shared_ptr<LightingDemo> m_lightingDemo;
        std::shared_ptr<MeshRenderer> m_meshRenderer;
    };
}