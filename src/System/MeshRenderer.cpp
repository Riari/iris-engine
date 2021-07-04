#include <glm/ext.hpp>

#include "Entity/Component/Camera.hpp"
#include "Entity/Component/Material.hpp"
#include "Entity/Component/Mesh.hpp"
#include "Entity/Component/DirectionalLight.hpp"
#include "Entity/Component/PointLight.hpp"
#include "Entity/Component/SpotLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "Utility/Logger.hpp"
#include "Scene/Scene.hpp"
#include "System/MeshRenderer.hpp"

using namespace Iris;

MeshRenderer::MeshRenderer()
{
    m_pBasicShaderProgram = std::make_unique<ShaderProgram>("Basic", Logger::GL);
    m_pBasicShaderProgram->Build();
    m_pMatShaderProg = std::make_unique<ShaderProgram>("Material", Logger::GL);
    m_pMatShaderProg->Build();
}

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

void MeshRenderer::SetPointLightId(EntityId id)
{
    m_pointLightId = id;
}

void MeshRenderer::SetSpotLightId(EntityId id)
{
    m_spotLightId = id;
}

void MeshRenderer::SetActiveCameraId(EntityId id)
{
    m_activeCameraId = id;
}

void MeshRenderer::Update(Window &window, Scene &scene)
{
    auto& directionalLight = GetComponent<DirectionalLight>(m_directionalLightId);
    auto& pointLightTransform = GetComponent<Transform>(m_pointLightId);
    auto& pointLight = GetComponent<PointLight>(m_pointLightId);
    auto& spotLightTransform = GetComponent<Transform>(m_spotLightId);
    auto& spotLight = GetComponent<SpotLight>(m_spotLightId);

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
            m_pMatShaderProg->Use();

            m_pMatShaderProg->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
            m_pMatShaderProg->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
            m_pMatShaderProg->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

            if (material.pDiffuseMap != nullptr)
            {
                material.pDiffuseMap->Bind(GL_TEXTURE0);
                m_pMatShaderProg->SetUniformInt("material.diffuse", 0);
            }

            if (material.pSpecularMap != nullptr)
            {
                material.pSpecularMap->Bind(GL_TEXTURE1);
                m_pMatShaderProg->SetUniformInt("material.specular", 1);
            }

            if (material.pEmissionMap != nullptr)
            {
                material.pEmissionMap->Bind(GL_TEXTURE2);
                m_pMatShaderProg->SetUniformInt("material.emission", 2);
            }

            m_pMatShaderProg->SetUniformFloat("material.shininess", material.shininess);

            m_pMatShaderProg->SetUniform3f("directionalLight.ambient", directionalLight.ambient);
            m_pMatShaderProg->SetUniform3f("directionalLight.diffuse", directionalLight.diffuse);
            m_pMatShaderProg->SetUniform3f("directionalLight.specular", directionalLight.specular);
            m_pMatShaderProg->SetUniform3f("directionalLight.direction", directionalLight.direction);

            m_pMatShaderProg->SetUniform3f("pointLightPos", pointLightTransform.position);
            m_pMatShaderProg->SetUniform3f("pointLight.ambient", pointLight.ambient);
            m_pMatShaderProg->SetUniform3f("pointLight.diffuse", pointLight.diffuse);
            m_pMatShaderProg->SetUniform3f("pointLight.specular", pointLight.specular);
            m_pMatShaderProg->SetUniformFloat("pointLight.constant", pointLight.constant);
            m_pMatShaderProg->SetUniformFloat("pointLight.linear", pointLight.linear);
            m_pMatShaderProg->SetUniformFloat("pointLight.quadratic", pointLight.quadratic);

            m_pMatShaderProg->SetUniform3f("spotLightPos", spotLightTransform.position);
            m_pMatShaderProg->SetUniform3f("spotLight.ambient", spotLight.ambient);
            m_pMatShaderProg->SetUniform3f("spotLight.diffuse", spotLight.diffuse);
            m_pMatShaderProg->SetUniform3f("spotLight.specular", spotLight.specular);
            m_pMatShaderProg->SetUniform3f("spotLight.direction", spotLight.direction);
            m_pMatShaderProg->SetUniformFloat("spotLight.innerEdge", spotLight.innerEdge);
            m_pMatShaderProg->SetUniformFloat("spotLight.outerEdge", spotLight.outerEdge);
            m_pMatShaderProg->SetUniformFloat("spotLight.constant", spotLight.constant);
            m_pMatShaderProg->SetUniformFloat("spotLight.linear", spotLight.linear);
            m_pMatShaderProg->SetUniformFloat("spotLight.quadratic", spotLight.quadratic);

            m_pMatShaderProg->SetUniformFloat("time", glfwGetTime());

            // TODO: remove this!
            if (id % 2 == 0) transform.rotation += 0.02f / transform.scale.x;
            else transform.rotation -= 0.02f / transform.scale.x;
        }

        mesh.pVao->Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
