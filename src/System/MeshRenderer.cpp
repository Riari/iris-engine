#include <glm/ext.hpp>

#include "Entity/Component/Camera.hpp"
#include "Entity/Component/Material.hpp"
#include "Entity/Component/Mesh.hpp"
#include "Entity/Component/DirectionalLight.hpp"
#include "Entity/Component/PointLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "Utility/Logger.hpp"
#include "Scene/Scene.hpp"
#include "System/MeshRenderer.hpp"

using namespace Iris;

MeshRenderer::MeshRenderer()
{
    m_pBasicShaderProgram = std::make_unique<ShaderProgram>("Basic", Logger::GL);
    m_pBasicShaderProgram->Build();
    m_pMaterialShaderProgram = std::make_unique<ShaderProgram>("Material", Logger::GL);
    m_pMaterialShaderProgram->Build();
}

std::list<ComponentType> MeshRenderer::GetComponentTypes()
{
    return {
        GetComponentType<Transform>(),
        GetComponentType<Mesh>(),
        GetComponentType<Material>()
    };
}

void MeshRenderer::SetPointLightId(EntityId id)
{
    m_pointLightId = id;
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
    auto& pointLightTransform = GetComponent<Transform>(m_pointLightId);
    auto& pointLight = GetComponent<PointLight>(m_pointLightId);
    auto& directionalLight = GetComponent<DirectionalLight>(m_directionalLightId);

    auto& camera = GetComponent<Camera>(m_activeCameraId);

    for (auto const& id : m_entities)
    {
        auto& transform = GetComponent<Transform>(id);
        auto& mesh = GetComponent<Mesh>(id);
        auto& material = GetComponent<Material>(id);

        if (material.pDiffuseMap == nullptr && material.pSpecularMap == nullptr && material.pEmissionMap == nullptr)
        {
            m_pBasicShaderProgram->Use();

            m_pBasicShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
            m_pBasicShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
            m_pBasicShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

            m_pBasicShaderProgram->SetUniform3f("objectColor", mesh.color);
        }
        else
        {
            m_pMaterialShaderProgram->Use();

            m_pMaterialShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
            m_pMaterialShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
            m_pMaterialShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

            if (material.pDiffuseMap != nullptr)
            {
                material.pDiffuseMap->Bind(GL_TEXTURE0);
                m_pMaterialShaderProgram->SetUniformInt("material.diffuse", 0);
            }

            if (material.pSpecularMap != nullptr)
            {
                material.pSpecularMap->Bind(GL_TEXTURE1);
                m_pMaterialShaderProgram->SetUniformInt("material.specular", 1);
            }

            if (material.pEmissionMap != nullptr)
            {
                material.pEmissionMap->Bind(GL_TEXTURE2);
                m_pMaterialShaderProgram->SetUniformInt("material.emission", 2);
            }

            m_pMaterialShaderProgram->SetUniformFloat("material.shininess", material.shininess);

            m_pMaterialShaderProgram->SetUniform3f("pointLightPos", pointLightTransform.position);
            m_pMaterialShaderProgram->SetUniform3f("pointLight.ambient", pointLight.ambient);
            m_pMaterialShaderProgram->SetUniform3f("pointLight.diffuse", pointLight.diffuse);
            m_pMaterialShaderProgram->SetUniform3f("pointLight.specular", pointLight.specular);
            m_pMaterialShaderProgram->SetUniformFloat("pointLight.constant", pointLight.constant);
            m_pMaterialShaderProgram->SetUniformFloat("pointLight.linear", pointLight.linear);
            m_pMaterialShaderProgram->SetUniformFloat("pointLight.quadratic", pointLight.quadratic);

            m_pMaterialShaderProgram->SetUniform3f("directionalLight.direction", directionalLight.direction);
            m_pMaterialShaderProgram->SetUniform3f("directionalLight.ambient", directionalLight.ambient);
            m_pMaterialShaderProgram->SetUniform3f("directionalLight.diffuse", directionalLight.diffuse);
            m_pMaterialShaderProgram->SetUniform3f("directionalLight.specular", directionalLight.specular);

            m_pMaterialShaderProgram->SetUniformFloat("time", glfwGetTime());
        }

        mesh.pVao->Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
