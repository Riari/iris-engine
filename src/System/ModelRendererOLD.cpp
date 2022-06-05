// #include <glm/ext.hpp>
// #include "Asset/AssetManager.hpp"
// #include "Entity/Component/Camera.hpp"
// #include "Entity/Component/Model.hpp"
// #include "Entity/Component/DirectionalLight.hpp"
// #include "Entity/Component/Transform.hpp"
// #include "Utility/Logger.hpp"
// #include "Scene/Scene.hpp"
// #include "ModelRenderer.hpp"

// using namespace Iris::OLD;

// std::list<ComponentType> ModelRenderer::GetComponentTypes()
// {
//     return {
//         GetComponentType<TransformComponent>(),
//         GetComponentType<ModelComponent>()
//     };
// }

// void ModelRenderer::SetDirectionalLightId(EntityId id)
// {
//     m_directionalLightId = id;
// }

// void ModelRenderer::SetActiveCameraId(EntityId id)
// {
//     m_activeCameraId = id;
// }

// void ModelRenderer::Update(Window &window, Scene &scene, bool debug)
// {
//     AssetManager& assetManager = AssetManager::GetInstance();
//     auto basicShaderProgram = assetManager.GetShaderProgram("Basic");
//     auto materialShaderProgram = assetManager.GetShaderProgram("Material");
//     auto shaderProgram = basicShaderProgram;

//     auto& directionalLight = GetComponent<DirectionalLightComponent>(m_directionalLightId);

//     auto& camera = GetComponent<CameraComponent>(m_activeCameraId);

//     for (auto const& id : m_entities)
//     {
//         auto& transform = GetComponent<TransformComponent>(id);
//         auto& model = GetComponent<ModelComponent>(id);
//         auto loadedTextures = model.pModel->GetLoadedTextures();

//         std::map<TextureDataType, std::shared_ptr<Texture>> textures {
//             { TextureDataType::Diffuse, nullptr },
//             { TextureDataType::Specular, nullptr },
//             { TextureDataType::Emission, nullptr },
//         };

//         for (auto const& texture : loadedTextures)
//         {
//             textures[texture.type] = texture.texture;
//         }

//         if (textures[TextureDataType::Diffuse] == nullptr && textures[TextureDataType::Specular] == nullptr && textures[TextureDataType::Emission] == nullptr)
//         {
//             shaderProgram->Use();

//             shaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
//             shaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
//             shaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

//             shaderProgram->SetUniform3f("objectColor", model.color);
//         }
//         else
//         {
//             shaderProgram = materialShaderProgram;
//             shaderProgram->Use();

//             shaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera.GetProjectionMatrix()));
//             shaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera.GetViewMatrix()));
//             shaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(transform.GetModel()));

//             if (textures[TextureDataType::Diffuse] != nullptr)
//             {
//                 textures[TextureDataType::Diffuse]->Bind(GL_TEXTURE0);
//                 shaderProgram->SetUniformInt("material.diffuse", 0);
//             }

//             if (textures[TextureDataType::Specular] != nullptr)
//             {
//                 textures[TextureDataType::Specular]->Bind(GL_TEXTURE1);
//                 shaderProgram->SetUniformInt("material.specular", 1);
//             }

//             if (textures[TextureDataType::Emission] != nullptr)
//             {
//                 textures[TextureDataType::Emission]->Bind(GL_TEXTURE2);
//                 shaderProgram->SetUniformInt("material.emission", 2);
//             }

//             shaderProgram->SetUniformFloat("material.shininess", 0.0);

//             shaderProgram->SetUniformFloat("time", glfwGetTime());

//             shaderProgram->SetUniform3f("viewPosition", camera.position);

//             shaderProgram->SetUniform3f("directionalLight.ambient", directionalLight.ambient);
//             shaderProgram->SetUniform3f("directionalLight.diffuse", directionalLight.diffuse);
//             shaderProgram->SetUniform3f("directionalLight.specular", directionalLight.specular);
//             shaderProgram->SetUniform3f("directionalLight.direction", directionalLight.direction);
//         }

//         model.pModel->Draw(shaderProgram);
//     }
// }
