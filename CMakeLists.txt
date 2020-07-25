cmake_minimum_required(VERSION 3.16)
project(GLSandbox)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(EXT_DIR "${CMAKE_SOURCE_DIR}/external")
set(GLAD_DIR "${EXT_DIR}/glad")
set(KHR_DIR "${EXT_DIR}/KHR")
set(GLFW_DIR "${EXT_DIR}/glfw")
set(SPDLOG_DIR "${EXT_DIR}/spdlog")
set(STB_DIR "${EXT_DIR}/stb")

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_library(glad "${GLAD_DIR}/include/glad/glad.h" "${GLAD_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${KHR_DIR}/include")

include_directories("${GLAD_DIR}/include")
include_directories("${STB_DIR}")

add_subdirectory(${GLFW_DIR})
add_subdirectory(${SPDLOG_DIR})

set(HEADERS
        "${SRC_DIR}/Asset/AssetManager.h"
        "${SRC_DIR}/Asset/AssetRepository.h"
        "${SRC_DIR}/Asset/Image.h"
        "${SRC_DIR}/Asset/ImageRepository.h"
        "${SRC_DIR}/Exception/Exception.h"
        "${SRC_DIR}/GL/Shader/FragmentShader.h"
        "${SRC_DIR}/GL/Shader/Shader.h"
        "${SRC_DIR}/GL/Shader/ShaderProgram.h"
        "${SRC_DIR}/GL/Shader/VertexShader.h"
        "${SRC_DIR}/GL/BufferObject.h"
        "${SRC_DIR}/GL/EBO.h"
        "${SRC_DIR}/GL/Texture.h"
        "${SRC_DIR}/GL/VAO.h"
        "${SRC_DIR}/GL/VBO.h")

set(SOURCES
        "${SRC_DIR}/Asset/AssetManager.cpp"
        "${SRC_DIR}/Asset/Image.cpp"
        "${SRC_DIR}/Asset/ImageRepository.cpp"
        "${SRC_DIR}/Exception/Exception.cpp"
        "${SRC_DIR}/GL/Shader/FragmentShader.cpp"
        "${SRC_DIR}/GL/Shader/Shader.cpp"
        "${SRC_DIR}/GL/Shader/ShaderProgram.cpp"
        "${SRC_DIR}/GL/Shader/VertexShader.cpp"
        "${SRC_DIR}/GL/BufferObject.cpp"
        "${SRC_DIR}/GL/EBO.cpp"
        "${SRC_DIR}/GL/Texture.cpp"
        "${SRC_DIR}/GL/VAO.cpp"
        "${SRC_DIR}/GL/VBO.cpp"
        "${SRC_DIR}/main.cpp")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

add_custom_target(copy-assets ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${CMAKE_BINARY_DIR}/assets")
add_custom_target(copy-shader-sources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${SRC_DIR}/GL/Shader/Source" "${CMAKE_BINARY_DIR}/resources/shaders")

add_dependencies(${PROJECT_NAME} copy-assets copy-shader-sources)

target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}/GL")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad spdlog)