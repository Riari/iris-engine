#include <glad/glad.h>
#include <glm/ext.hpp>
#include <utility>

#include "Demo/ColoredCube.hpp"
#include "GL/VAO.hpp"
#include "GL/Shader/ShaderProgram.hpp"
#include "Utility/Logger.hpp"

using namespace OGLDemo;

ColoredCube::ColoredCube(std::string id, glm::vec3 position, glm::vec3 color, glm::vec3 lightColor, glm::vec3 lightPos) : OGL::RenderableEntity(std::move(id), position)
{
    auto *pVao = new OGL::VAO();
    pVao->Bind();
    OGL::VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    OGL::VBO::SetVertexAttribute(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    OGL::VAO::Unbind();

    auto pProgram = std::make_shared<OGL::ShaderProgram>("ColoredCube", OGL::Logger::GL);
    pProgram->Build();
    pProgram->Use();
    pProgram->SetUniform3f("objectColor", color);
    pProgram->SetUniform3f("lightColor", lightColor);
    pProgram->SetUniform3f("lightPos", lightPos);

    SetVAO(*pVao);
    SetShaderProgram(pProgram);
}

void ColoredCube::Render(std::shared_ptr<OGL::Camera> camera)
{
    m_shaderProgram->Use();
    m_shaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera->GetProjectionMatrix()));
    m_shaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera->GetViewMatrix()));
    m_shaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(m_model));
    m_shaderProgram->SetUniform3f("viewPos", camera->GetPosition());

    m_vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
