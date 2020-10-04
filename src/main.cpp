#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include "Asset/AssetManager.h"
#include "GL/Shader/ShaderProgram.h"
#include "GL/Camera.h"
#include "GL/EBO.h"
#include "GL/VAO.h"
#include "GL/VBO.h"
#include "GL/Texture.h"

void processKeyboardInput(GLFWwindow *window);

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

void cursorPosCallback(GLFWwindow *window, double x, double y);

void scrollCallback(GLFWwindow *window, double x, double y);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));

float lastMouseX = SCREEN_WIDTH / 2, lastMouseY = SCREEN_HEIGHT / 2;
bool firstMouse = true;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "GLSandbox", NULL, NULL);
    if (window == NULL)
    {
        spdlog::critical("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);

    spdlog::info("Window created");

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        spdlog::critical("Failed to initialize GLAD");
        return -1;
    }

    spdlog::info("GLAD initialized");

    auto *basicShaderProgram = new ShaderProgram("Basic");
    basicShaderProgram->Compile();
    basicShaderProgram->Link();
    basicShaderProgram->DeleteShaders();

    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    VAO *vao = new VAO();
    VBO *vbo = new VBO();

    vao->Bind();
    vbo->Bind();
    vbo->SetData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    VBO::SetVertexAttribute(0, 3, 5 * sizeof(float), (void *) 0); // position
    VBO::SetVertexAttribute(1, 2, 5 * sizeof(float), (void *) (3 * sizeof(float))); // texture

    auto *assetManager = new AssetManager();
    ImageRepository::SetFlipVerticallyOnLoad(true);
    std::shared_ptr<Image> containerImage = assetManager->GetImage("assets/textures/container.jpg");
    std::shared_ptr<Image> faceImage = assetManager->GetImage("assets/textures/febby.png");

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
    faceTexture->Define(true);
    assetManager->UnloadImage(faceImage->GetPath());

    vbo->Unbind();
    VAO::Unbind();

    basicShaderProgram->Use();
    basicShaderProgram->SetUniformInt("texture1", 0);
    basicShaderProgram->SetUniformInt("texture2", 1);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processKeyboardInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        containerTexture->Bind(GL_TEXTURE0);
        faceTexture->Bind(GL_TEXTURE1);

        // Projection matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.GetFOV()), (float) (SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f,
                                      100.0f);
        basicShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(projection));

        // View matrix
        glm::mat4 view = camera.GetViewMatrix();
        basicShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(view));

        basicShaderProgram->SetUniformFloat("blend", 0.5);

        vao->Bind();
        for (unsigned int i = 0; i < std::size(cubePositions); i++)
        {
            // Model matrix
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = (i % 3 == 0) ? glfwGetTime() * 25.0f : i * 20.0f;

            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            basicShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete vao;
    delete vbo;
    delete assetManager;
    delete containerTexture;
    delete faceTexture;
    delete basicShaderProgram;

    glfwTerminate();
    return 0;
}

void processKeyboardInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float speedModifier = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speedModifier = 4.0f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.Move(CameraMovement::FORWARD, deltaTime, speedModifier);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.Move(CameraMovement::BACKWARD, deltaTime, speedModifier);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.Move(CameraMovement::LEFT, deltaTime, speedModifier);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.Move(CameraMovement::RIGHT, deltaTime, speedModifier);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.Move(CameraMovement::UP, deltaTime, speedModifier);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) camera.Move(CameraMovement::DOWN, deltaTime, speedModifier);
}

void cursorPosCallback(GLFWwindow *window, double x, double y)
{
    if (firstMouse)
    {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    float xOffset = x - lastMouseX;
    float yOffset = lastMouseY - y;

    lastMouseX = x;
    lastMouseY = y;

    camera.Rotate(xOffset, yOffset, deltaTime);
}

void scrollCallback(GLFWwindow *window, double x, double y)
{
    camera.AdjustFOV(y);
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
