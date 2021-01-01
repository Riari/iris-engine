#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
#include <cxxopts.hpp>

#include "Controller/CameraController.h"
#include "GL/Shader/ShaderProgram.h"

#if !defined(NDEBUG)
#include "GL/Debug.h"
#endif

#include "GL/EBO.h"
#include "GL/VAO.h"
#include "GL/VBO.h"
#include "GL/Texture.h"
#include "Window/Window.h"

using namespace OGL;

int main(int argc, char** argv)
{
    cxxopts::Options options("GLSandbox", "GL stuff.");

    options.add_options()
            ("f,maxfps", "Maximum FPS", cxxopts::value<double>()->default_value("60"))
    ;

    auto opts = options.parse(argc, argv);

    Utility::Logger::Init();

    auto *window = new Window::Window("LearnOpenGL", Utility::Logger::WINDOW, 1440, 900);

    auto inputManager = std::make_shared<Input::InputManager>();
    window->RegisterKeyHandler(inputManager.get());

    auto camera = std::make_shared<GL::Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    camera->SetRotateSpeed(100);
    auto *cameraController = new Controller::CameraController(camera, inputManager);
    window->RegisterCursorPosHandler(cameraController);
    window->RegisterScrollHandler(cameraController);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        Utility::Logger::MAIN->critical("Failed to initialize GLAD");
        return -1;
    }

    Utility::Logger::MAIN->info("GLAD initialized");

#if !defined(NDEBUG)
    InitGLDebug();
#endif

    float cubeVertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // Cube VBO

    auto *cubeVBO = new GL::VBO();
    cubeVBO->Bind();
    cubeVBO->SetData(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Light source cube

    auto *lightSourceVAO = new GL::VAO();
    lightSourceVAO->Bind();
    GL::VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    GL::VAO::Unbind();

    auto *lightSourceShaderProgram = new GL::ShaderProgram("LightSource", Utility::Logger::GL);
    lightSourceShaderProgram->Build();

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    // Coloured cube

    auto *coloredCubeVAO = new GL::VAO();
    coloredCubeVAO->Bind();
    GL::VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    GL::VBO::SetVertexAttribute(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    GL::VAO::Unbind();

    auto *coloredCubeShaderProgram = new GL::ShaderProgram("ColoredCube", Utility::Logger::GL);
    coloredCubeShaderProgram->Build();
    coloredCubeShaderProgram->Use();
    coloredCubeShaderProgram->SetUniform3f("objectColor", {1.0f, 0.5f, 0.31f});
    coloredCubeShaderProgram->SetUniform3f("lightColor", {1.0f, 1.0f, 1.0f});
    coloredCubeShaderProgram->SetUniform3f("lightPos", {lightPos[0], lightPos[1], lightPos[2]});

    glEnable(GL_DEPTH_TEST);

    const double fpsLimit = 1.0 / opts["maxfps"].as<double>();
    double lastUpdateTime = 0;
    double lastFrameTime = 0;
    double fpsTime = 0;
    int frameCount = 0;

    while (!glfwWindowShouldClose(window->GetGLFWWindow()))
    {
        double now = glfwGetTime();
        double deltaTime = now - lastUpdateTime;
        fpsTime += deltaTime;

        cameraController->Update(deltaTime);

        if (fpsTime >= 1.0) {
            window->SetTitle(("GLSandbox | " + std::to_string(frameCount) + " FPS").c_str());
            fpsTime -= 1.0;
            frameCount = 0;
        }

        if ((now - lastFrameTime) >= fpsLimit)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Projection matrix
            glm::mat4 projection = glm::perspective(glm::radians(camera->GetFOV()), (float) window->GetScreenWidth() / (float) window->GetScreenHeight(), 0.1f, 100.0f);

            // View matrix
            glm::mat4 view = camera->GetViewMatrix();

            // Render colored cube
            coloredCubeShaderProgram->Use();
            coloredCubeShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(projection));
            coloredCubeShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(view));
            glm::mat4 model = glm::mat4(1.0f);
            coloredCubeShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(model));

            coloredCubeVAO->Bind();

            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Render light source
            lightSourceShaderProgram->Use();
            lightSourceShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(projection));
            lightSourceShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(view));
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));
            lightSourceShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(model));

            lightSourceVAO->Bind();

            glDrawArrays(GL_TRIANGLES, 0, 36);

            glfwSwapBuffers(window->GetGLFWWindow());

            frameCount++;
            lastFrameTime = now;
        }

        glfwPollEvents();

        lastUpdateTime = now;
    }

    delete coloredCubeVAO;
    delete cubeVBO;
    delete cameraController;
    delete window;

    glfwTerminate();
    return 0;
}