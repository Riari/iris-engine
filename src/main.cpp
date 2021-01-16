#include <string>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
#include <cxxopts.hpp>

#include "Demo/CameraController.hpp"
#include "Demo/Keys.hpp"
#include "GL/Shader/ShaderProgram.hpp"

#if !defined(NDEBUG)
#include "GL/Debug.hpp"
#endif

#include "GL/EBO.hpp"
#include "GL/Texture.hpp"
#include "GL/VAO.hpp"
#include "GL/VBO.hpp"
#include "Input/InputManager.hpp"
#include "Window/WindowManager.hpp"
#include "Utility/Logger.hpp"

using namespace OGLDemo;

int main(int argc, char** argv)
{
    cxxopts::Options options("GLSandbox", "GL stuff.");

    options.add_options()
            ("f,maxfps", "Maximum FPS", cxxopts::value<double>()->default_value("60"))
    ;

    auto opts = options.parse(argc, argv);

    OGL::Logger::Init();

    glfwInit();
    glfwSetErrorCallback([](int error_code, const char* description) { OGL::Logger::GL->error(description); });

    OGL::InputManager::RegisterBinding(Keys::MoveForward, GLFW_KEY_W);
    OGL::InputManager::RegisterBinding(Keys::MoveBackward, GLFW_KEY_S);
    OGL::InputManager::RegisterBinding(Keys::StrafeLeft, GLFW_KEY_A);
    OGL::InputManager::RegisterBinding(Keys::StrafeRight, GLFW_KEY_D);
    OGL::InputManager::RegisterBinding(Keys::Ascend, GLFW_KEY_SPACE);
    OGL::InputManager::RegisterBinding(Keys::Descend, GLFW_KEY_C);

    const int WINDOW_MAIN = 0;

    OGL::WindowManager& windowManager = OGL::WindowManager::GetInstance();
    OGL::Window& mainWindow = windowManager.Create(WINDOW_MAIN, "", 1440, 900);
    mainWindow.MakeCurrent();

    auto camera = std::make_shared<OGL::Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    camera->SetRotateSpeed(10);
    auto *cameraController = new CameraController(camera);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        OGL::Logger::MAIN->critical("Failed to initialize GLAD");
        return -1;
    }

    OGL::Logger::MAIN->info("GLAD initialized");

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

    auto *cubeVBO = new VBO();
    cubeVBO->Bind();
    cubeVBO->SetData(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Light source cube

    auto *lightSourceVAO = new VAO();
    lightSourceVAO->Bind();
    OGL::VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    OGL::VAO::Unbind();

    auto *lightSourceShaderProgram = new ShaderProgram("LightSource", OGL::Logger::GL);
    lightSourceShaderProgram->Build();

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    // Coloured cube

    auto *coloredCubeVAO = new VAO();
    coloredCubeVAO->Bind();
    OGL::VBO::SetVertexAttribute(0, 3, 6 * sizeof(float), (void*)0);
    OGL::VBO::SetVertexAttribute(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    OGL::VAO::Unbind();

    auto *coloredCubeShaderProgram = new ShaderProgram("ColoredCube", OGL::Logger::GL);
    coloredCubeShaderProgram->Build();
    coloredCubeShaderProgram->Use();
    coloredCubeShaderProgram->SetUniform3f("objectColor", {1.0f, 0.5f, 0.31f});
    coloredCubeShaderProgram->SetUniform3f("lightColor", {1.0f, 1.0f, 1.0f});
    coloredCubeShaderProgram->SetUniform3f("lightPos", {lightPos[0], lightPos[1], lightPos[2]});

    glEnable(GL_DEPTH_TEST);

    const double maxFPS = opts["maxfps"].as<double>();
    const double updateFrequency = 1.0 / std::max(maxFPS, 120.0);
    const double frameFrequency = 1.0 / maxFPS;
    double lastUpdateTime = 0;
    double lastFrameTime = 0;
    double lastLoopTime = 0;
    double fpsTime = 0;
    int frameCount = 0;

    while (!mainWindow.ShouldClose())
    {
        double now = glfwGetTime();
        fpsTime += now - lastLoopTime;

        if (fpsTime >= 1.0) {
            mainWindow.SetTitle(("GLSandbox | " + std::to_string(frameCount) + " FPS").c_str());
            fpsTime -= 1.0;
            frameCount = 0;
        }

        double deltaTime = now - lastUpdateTime;
        if (deltaTime >= updateFrequency) {
            glfwPollEvents();

            cameraController->Update(deltaTime);

            lastUpdateTime = now;
        }

        if ((now - lastFrameTime) >= frameFrequency)
        {
            int *pBufferSize = mainWindow.GetFramebufferSize();
            glViewport(0, 0, pBufferSize[0], pBufferSize[1]);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Projection matrix
            glm::mat4 projection = glm::perspective(glm::radians(camera->GetFOV()), (float) pBufferSize[0] / (float) pBufferSize[1], 0.1f, 100.0f);

            // View matrix
            glm::mat4 view = camera->GetViewMatrix();

            // Render colored cube
            coloredCubeShaderProgram->Use();
            coloredCubeShaderProgram->SetUniformMatrix4fv("projection", glm::value_ptr(projection));
            coloredCubeShaderProgram->SetUniformMatrix4fv("view", glm::value_ptr(view));
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(135.0f), glm::vec3(1, 1, 1));
            model = glm::scale(model, glm::vec3(0.8f, 1.0f, 1.2f));
            coloredCubeShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(model));
            auto cameraPos = camera->GetPosition();
            coloredCubeShaderProgram->SetUniform3f("viewPos", {cameraPos[0], cameraPos[1], cameraPos[2]});

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

            mainWindow.SwapBuffers();

            frameCount++;
            lastFrameTime = now;
        }

        lastLoopTime = now;
    }

    delete coloredCubeVAO;
    delete cubeVBO;

    return 0;
}