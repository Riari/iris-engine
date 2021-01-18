#include <glad/glad.h>
#include <glm/ext.hpp>

#include "Demo/LightCube.hpp"
#include "Utility/Logger.hpp"

using namespace OGLDemo;

LightCube::LightCube(int id, glm::vec3 position) : OGL::RenderableEntity(id, position)
{
    auto *pVao = new OGL::VAO();
    pVao->Bind();
    OGL::VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    OGL::VAO::Unbind();

    auto pProgram = std::make_shared<OGL::ShaderProgram>("LightSource", OGL::Logger::GL);
    pProgram->Build();

    SetVAO(*pVao);
    SetShaderProgram(pProgram);
}

void LightCube::Render(std::shared_ptr<OGL::Camera> camera)
{
    m_shaderProgram->Use();
    m_shaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(camera->GetProjectionMatrix()));
    m_shaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(camera->GetViewMatrix()));
    m_shaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(m_model));

    m_vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
