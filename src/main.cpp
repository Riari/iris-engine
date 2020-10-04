#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include "Asset/AssetManager.h"
#include "Controller/CameraController.h"
#include "GL/Shader/ShaderProgram.h"
#include "GL/Camera.h"
#include "GL/EBO.h"
#include "GL/VAO.h"
#include "GL/VBO.h"
#include "GL/Texture.h"
#include "Input/InputManager.h"
#include "Utility/Timer.h"
#include "Window/Window.h"

int main()
{
    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, -3.0f));
    auto *window = new Window("LearnOpenGL");
    auto timer = std::make_shared<Timer>();

    auto inputManager = std::make_shared<InputManager>();
    window->RegisterKeyHandler(inputManager.get());

    auto *cameraController = new CameraController(camera, inputManager);
    window->RegisterCursorPosHandler(cameraController);
    window->RegisterScrollHandler(cameraController);

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

    while (!glfwWindowShouldClose(window->GetGLFWWindow()))
    {
        timer->Tick();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        containerTexture->Bind(GL_TEXTURE0);
        faceTexture->Bind(GL_TEXTURE1);

        // Projection matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera->GetFOV()), (float) (window->GetScreenWidth() / window->GetScreenHeight()), 0.1f,
                                      100.0f);
        basicShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(projection));

        // View matrix
        glm::mat4 view = camera->GetViewMatrix();
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

        glfwSwapBuffers(window->GetGLFWWindow());
        glfwPollEvents();

        cameraController->Update(timer->GetDeltaTime());
    }

    delete vao;
    delete vbo;
    delete assetManager;
    delete containerTexture;
    delete faceTexture;
    delete basicShaderProgram;
    delete cameraController;
    delete window;

    glfwTerminate();
    return 0;
}