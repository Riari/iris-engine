#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "Asset/AssetManager.h"
#include "GL/Shader/ShaderProgram.h"
#include "GL/EBO.h"
#include "GL/VAO.h"
#include "GL/VBO.h"
#include "GL/Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLSandbox", NULL, NULL);
    if (window == NULL)
    {
        spdlog::critical("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    spdlog::info("Window created");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::critical("Failed to initialize GLAD");
        return -1;
    }

    spdlog::info("GLAD initialized");

    auto* triangleShaderProgram = new ShaderProgram("Triangle");
    triangleShaderProgram->Compile();
    triangleShaderProgram->Link();
    triangleShaderProgram->DeleteShaders();

    float vertices[] = {
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    VAO *vao = new VAO();
    VBO *vbo = new VBO();
    EBO *ebo = new EBO();

    vao->Bind();
    vbo->Bind();
    ebo->Bind();

    vbo->SetData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    VBO::SetVertexAttribute(0, 3, 6 * sizeof(float)); // position
    VBO::SetVertexAttribute(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float))); // colour
    VBO::SetVertexAttribute(2, 2, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texture

    ebo->SetData(sizeof(indices), indices, GL_STATIC_DRAW);

    auto *assetManager = new AssetManager();
    std::shared_ptr<Image> wallImage = assetManager->GetImage("assets/textures/wall.jpg");
    auto wallTexture = new Texture(wallImage);
    wallTexture->Bind();
    Texture::SetWrapMethod(GL_REPEAT);
    Texture::SetFilterMethod(GL_LINEAR);
    wallTexture->Generate();
    Texture::GenerateMipmap();
    assetManager->UnloadImage(wallImage->GetPath());

    vbo->Unbind();
    VAO::Unbind();
    ebo->Unbind();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        wallTexture->Bind();

        triangleShaderProgram->Use();

        //float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

        //triangleShaderProgram->SetUniform4f("ourColor", std::vector<float> { 1.0f, greenValue, 0.0f, 1.0f });

        vao->Bind();
        ebo->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete vao;
    delete vbo;
    delete ebo;
    delete assetManager;
    delete wallTexture;
    delete triangleShaderProgram;

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

