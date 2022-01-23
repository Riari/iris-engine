#include <glm/ext.hpp>

#include "Asset/AssetManager.hpp"
#include "Entity/Component/CameraComponent.hpp"
#include "Entity/Component/ModelComponent.hpp"
#include "Entity/Component/DirectionalLightComponent.hpp"
#include "Entity/Component/TransformComponent.hpp"
#include "Utility/Logger.hpp"
#include "Scene/Scene.hpp"
#include "System/ModelRenderer.hpp"

using namespace Iris;

std::list<ComponentType> ModelRenderer::GetComponentTypes()
{
    return {
        GetComponentType<TransformComponent>(),
        GetComponentType<ModelComponent>()
    };
}

void ModelRenderer::SetDirectionalLightId(EntityId id)
{
    m_directionalLightId = id;
}

void ModelRenderer::SetActiveCameraId(EntityId id)
{
    m_activeCameraId = id;
}

void ModelRenderer::Update(Window &window, Scene &scene, bool debug)
{
    AssetManager& assetManager = AssetManager::GetInstance();
    auto basicShaderProgram = assetManager.GetShaderProgram("Basic");
    auto materialShaderProgram = assetManager.GetShaderProgram("Material");
    auto shaderProgram = basicShaderProgram;

    auto& directionalLight = GetComponent<DirectionalLightComponent>(m_directionalLightId);

    auto& camera = GetComponent<CameraComponent>(m_activeCameraId);

    for (auto const& id : m_entities)
    {
        auto& transform = GetComponent<TransformComponent>(id);
        auto& model = GetComponent<ModelComponent>(id);
        auto loadedTextures = model.pModel->GetLoadedTextures();

        std::map<GLTextureType, std::shared_ptr<Texture>> textures {
            { GLTextureType::Diffuse, nullptr },
            { GLTextureType::Specular, nullptr },
            { GLTextureType::Emission, nullptr },
        };

        for (auto const& texture : loadedTextures)
        {
            textures[texture.type] = texture.texture;
        }

        if (textures[GLTextureType::Diffuse] == nullptr && textures[GLTextureType::Specular] == nullptr && textures[GLTextureType::Emission] == nullptr)
        {
            shaderProgram->Use();

            shaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
            shaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
            shaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

            shaderProgram->SetUniform3f("objectColor", model.color);
        }
        else
        {
            shaderProgram = materialShaderProgram;
            shaderProgram->Use();

            shaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
            shaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
            shaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

            if (textures[GLTextureType::Diffuse] != nullptr)
            {
                textures[GLTextureType::Diffuse]->Bind(GL_TEXTURE0);
                shaderProgram->SetUniformInt("material.diffuse", 0);
            }

            if (textures[GLTextureType::Specular] != nullptr)
            {
                textures[GLTextureType::Specular]->Bind(GL_TEXTURE1);
                shaderProgram->SetUniformInt("material.specular", 1);
            }

            if (textures[GLTextureType::Emission] != nullptr)
            {
                textures[GLTextureType::Emission]->Bind(GL_TEXTURE2);
                shaderProgram->SetUniformInt("material.emission", 2);
            }

            shaderProgram->SetUniformFloat("material.shininess", 0.0);

            shaderProgram->SetUniformFloat("time", glfwGetTime());

            shaderProgram->SetUniform3f("viewPosition", camera.position);

            shaderProgram->SetUniform3f("directionalLight.ambient", directionalLight.ambient);
            shaderProgram->SetUniform3f("directionalLight.diffuse", directionalLight.diffuse);
            shaderProgram->SetUniform3f("directionalLight.specular", directionalLight.specular);
            shaderProgram->SetUniform3f("directionalLight.direction", directionalLight.direction);
        }

        model.pModel->Draw(shaderProgram);
    }
}
