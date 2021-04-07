#include <glad/glad.h>
#include <glm/ext.hpp>

#include "Entity/Component/Camera.hpp"
#include "Entity/Component/Mesh.hpp"
#include "Entity/Component/PointLight.hpp"
#include "Entity/Component/Transform.hpp"
#include "System/MeshRenderer.hpp"

using namespace Iris;

std::list<ComponentType> MeshRenderer::GetComponentTypes()
{
    return {
        GetComponentType<Transform>(),
        GetComponentType<Mesh>()
    };
}

void MeshRenderer::SetPointLightId(EntityId id)
{
    m_pointLightId = id;
}

void MeshRenderer::SetActiveCameraId(EntityId id)
{
    m_activeCameraId = id;
}

void MeshRenderer::Update(Window &window)
{
    auto& lightTransform = GetComponent<Transform>(m_pointLightId);
    auto& lightPointLight = GetComponent<PointLight>(m_pointLightId);

    auto& camera = GetComponent<Camera>(m_activeCameraId);

    for (auto const& id : m_entities)
    {
        auto& transform = GetComponent<Transform>(id);
        auto& mesh = GetComponent<Mesh>(id);
        mesh.pShaderProgram->Use();
        mesh.pShaderProgram->SetUniform3f("objectColor", mesh.color);
        mesh.pShaderProgram->SetUniform3f("lightPos", lightTransform.position);
        mesh.pShaderProgram->SetUniform3f("lightColor", lightPointLight.color);
        mesh.pShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
        mesh.pShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
        mesh.pShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));
        mesh.pShaderProgram->SetUniform3f("viewPos", camera.position);

        mesh.pVao->Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}