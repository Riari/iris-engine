#include <glm/ext.hpp>

#include "Asset/AssetManager.hpp"
#include "Entity/Component/Camera.hpp"
#include "Entity/Component/Material.hpp"
#include "Entity/Component/Mesh.hpp"
#include "Entity/Component/DirectionalLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "Utility/Logger.hpp"
#include "Scene/Scene.hpp"
#include "System/MeshRenderer.hpp"

using namespace Iris;

std::list<ComponentType> MeshRenderer::GetComponentTypes()
{
    return {
        GetComponentType<Transform>(),
        GetComponentType<Mesh>(),
        GetComponentType<Material>()
    };
}

void MeshRenderer::SetDirectionalLightId(EntityId id)
{
    m_directionalLightId = id;
}

void MeshRenderer::SetActiveCameraId(EntityId id)
{
    m_activeCameraId = id;
}

void MeshRenderer::Update(Window &window, Scene &scene)
{
    AssetManager& assetManager = AssetManager::GetInstance();
    auto basicShaderProgram = assetManager.GetShaderProgram("Basic");
    auto materialShaderProgram = assetManager.GetShaderProgram("Material");

    auto& directionalLight = GetComponent<DirectionalLight>(m_directionalLightId);

    auto& camera = GetComponent<Camera>(m_activeCameraId);

    for (auto const& id : m_entities)
    {
        auto& transform = GetComponent<Transform>(id);
        auto& mesh = GetComponent<Mesh>(id);
        auto& material = GetComponent<Material>(id);

        if (material.pDiffuseMap == nullptr && material.pSpecularMap == nullptr && material.pEmissionMap == nullptr)
        {
            basicShaderProgram->Use();

            basicShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
            basicShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
            basicShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

            basicShaderProgram->SetUniform3f("objectColor", mesh.color);
        }
        else
        {
            materialShaderProgram->Use();

            materialShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
            materialShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
            materialShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

            if (material.pDiffuseMap != nullptr)
            {
                material.pDiffuseMap->Bind(GL_TEXTURE0);
                materialShaderProgram->SetUniformInt("material.diffuse", 0);
            }

            if (material.pSpecularMap != nullptr)
            {
                material.pSpecularMap->Bind(GL_TEXTURE1);
                materialShaderProgram->SetUniformInt("material.specular", 1);
            }

            if (material.pEmissionMap != nullptr)
            {
                material.pEmissionMap->Bind(GL_TEXTURE2);
                materialShaderProgram->SetUniformInt("material.emission", 2);
            }

            materialShaderProgram->SetUniformFloat("material.shininess", material.shininess);

            materialShaderProgram->SetUniformFloat("time", glfwGetTime());

            materialShaderProgram->SetUniform3f("viewPosition", camera.position);

            materialShaderProgram->SetUniform3f("directionalLight.ambient", directionalLight.ambient);
            materialShaderProgram->SetUniform3f("directionalLight.diffuse", directionalLight.diffuse);
            materialShaderProgram->SetUniform3f("directionalLight.specular", directionalLight.specular);
            materialShaderProgram->SetUniform3f("directionalLight.direction", directionalLight.direction);

            // TODO: remove this!
            if (id % 2 == 0) transform.rotation += 0.02f / transform.scale.x;
            else transform.rotation -= 0.02f / transform.scale.x;
        }

        mesh.pVao->Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
