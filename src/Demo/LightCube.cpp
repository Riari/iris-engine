#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <utility>

#include "Demo/LightCube.hpp"
#include "Utility/Logger.hpp"

using namespace IrisDemo;

LightCube::LightCube(std::string id, glm::vec3 position, glm::vec3 emissionColor) : Iris::Entity(std::move(id), position), m_emissionColor(emissionColor)
{
    auto *pVao = new Iris::VAO();
    pVao->Bind();
    Iris::VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    Iris::VAO::Unbind();

    auto pProgram = std::make_shared<Iris::ShaderProgram>("LightSource", Iris::Logger::GL);
    pProgram->Build();

    SetVAO(*pVao);
    SetShaderProgram(pProgram);
}

void LightCube::Render(std::shared_ptr<Iris::Camera> camera)
{
    GetTransform().SetPosition(glm::vec3(1.0f + sin(glfwGetTime()) * 2.0f, sin(glfwGetTime() / 2.0f) * 1.0f, 0.0f));

    m_shaderProgram->Use();
    m_shaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera->GetProjectionMatrix()));
    m_shaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera->GetViewMatrix()));
    m_shaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(GetTransform().GetModel()));

    m_vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

glm::vec3 LightCube::GetEmissionColor()
{
    return m_emissionColor;
}
