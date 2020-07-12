#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <spdlog\spdlog.h>

#include "GL/VAO.h"
#include "GL/VBO.h"
#include "GL/Shader/ShaderProgram.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        spdlog::critical("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    spdlog::info("Window created");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::critical("Failed to initialize GLAD");
        return -1;
    }

    spdlog::info("GLAD initialized");

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    auto* triangleShaderProgram = new ShaderProgram("Triangle");
    triangleShaderProgram->Compile();
    triangleShaderProgram->Link();
    triangleShaderProgram->Release();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    VAO vao;
    VBO vbo;
    vao.Bind();
    vbo.Bind();
    vbo.SetData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    VBO::SetVertexAttribute(0, 3);

    vbo.Unbind();
    VAO::Unbind();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        triangleShaderProgram->Use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vbo.Release();
    vao.Release();
    delete triangleShaderProgram;

    glfwTerminate();

    return 0;
}