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
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
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
    vbo->SetData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    ebo->Bind();
    ebo->SetData(sizeof(indices), indices, GL_STATIC_DRAW);

    VBO::SetVertexAttribute(0, 3, 8 * sizeof(float), (void*)0); // position
    VBO::SetVertexAttribute(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float))); // colour
    VBO::SetVertexAttribute(2, 2, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texture

    auto *assetManager = new AssetManager();
    ImageRepository::SetFlipVerticallyOnLoad(true);
    std::shared_ptr<Image> containerImage = assetManager->GetImage("assets/textures/container.jpg");
    std::shared_ptr<Image> faceImage = assetManager->GetImage("assets/textures/awesomeface.png");

    auto containerTexture = new Texture(containerImage);
    containerTexture->Bind(GL_TEXTURE0);
    Texture::SetWrapMethod(GL_REPEAT);
    Texture::SetFilterMethod(GL_LINEAR);
    containerTexture->Define(true);
    assetManager->UnloadImage(containerImage->GetPath());

    auto faceTexture = new Texture(faceImage);
    faceTexture->Bind(GL_TEXTURE1);
    Texture::SetWrapMethod(GL_REPEAT);
    Texture::SetFilterMethod(GL_LINEAR);
    faceTexture->Define(GL_RGBA, true);
    assetManager->UnloadImage(faceImage->GetPath());

    vbo->Unbind();
    VAO::Unbind();
    ebo->Unbind();

    triangleShaderProgram->Use();
    triangleShaderProgram->SetUniformInt("texture1", 0);
    triangleShaderProgram->SetUniformInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        containerTexture->Bind(GL_TEXTURE0);
        faceTexture->Bind(GL_TEXTURE1);

        triangleShaderProgram->Use();

        vao->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete vao;
    delete vbo;
    delete ebo;
    delete assetManager;
    delete containerTexture;
    delete faceTexture;
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

