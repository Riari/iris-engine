#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Logging.h"

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

int main()
{
    spdlog::set_pattern(LOG_PATTERN);
    auto loggerWindow = spdlog::stdout_color_mt(LOGGER_WINDOW);
    auto loggerGL = spdlog::stdout_color_mt(LOGGER_GL);
    auto loggerMain = spdlog::stdout_color_mt("Main");

#if !defined(NDEBUG)
    spdlog::set_level(spdlog::level::debug);
#endif

    auto *window = new Window("LearnOpenGL", loggerWindow);
    auto timer = std::make_shared<Timer>();

    auto inputManager = std::make_shared<InputManager>();
    window->RegisterKeyHandler(inputManager.get());

    auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    auto *cameraController = new CameraController(camera, inputManager);
    window->RegisterCursorPosHandler(cameraController);
    window->RegisterScrollHandler(cameraController);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        loggerMain->critical("Failed to initialize GLAD");
        return -1;
    }

    loggerMain->info("GLAD initialized");

#if !defined(NDEBUG)
    InitGLDebug();
#endif

    float cubeVertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };

    // Cube VBO

    VBO *cubeVBO = new VBO();
    cubeVBO->Bind();
    cubeVBO->SetData(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Coloured cube

    VAO *coloredCubeVAO = new VAO();
    coloredCubeVAO->Bind();
    VBO::SetVertexAttribute(0, 3, 3 * sizeof(float), (void*)0);
    VAO::Unbind();

    auto *coloredCubeShaderProgram = new ShaderProgram("ColoredCube", loggerGL);
    coloredCubeShaderProgram->Compile();
    coloredCubeShaderProgram->Link();
    coloredCubeShaderProgram->DeleteShaders();
    coloredCubeShaderProgram->Use();
    coloredCubeShaderProgram->SetUniform3f("objectColor", {1.0f, 0.5f, 0.31f});
    coloredCubeShaderProgram->SetUniform3f("lightColor", {1.0f, 1.0f, 1.0f});

    // Light source cube

    VAO *lightSourceVAO = new VAO();
    lightSourceVAO->Bind();
    VBO::SetVertexAttribute(0, 3, 3 * sizeof(float), (void*)0);
    VAO::Unbind();

    auto *lightSourceShaderProgram = new ShaderProgram("LightSource", loggerGL);
    lightSourceShaderProgram->Compile();
    lightSourceShaderProgram->Link();
    lightSourceShaderProgram->DeleteShaders();

    glm::vec3 lightSourcePosition(1.2f, 1.0f, 2.0f);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window->GetGLFWWindow()))
    {
        timer->Tick();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera->GetFOV()), (float) (window->GetScreenWidth() / window->GetScreenHeight()), 0.1f, 100.0f);

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
        model = glm::translate(model, lightSourcePosition);
        model = glm::scale(model, glm::vec3(0.2f));
        lightSourceShaderProgram->SetUniformMatrix4fv("model", glm::value_ptr(model));

        lightSourceVAO->Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window->GetGLFWWindow());
        glfwPollEvents();

        cameraController->Update(timer->GetDeltaTime());
    }

    delete coloredCubeVAO;
    delete cubeVBO;
    delete cameraController;
    delete window;

    glfwTerminate();
    return 0;
}