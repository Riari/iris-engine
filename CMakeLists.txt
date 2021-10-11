cmake_minimum_required(VERSION 3.16)
project(IrisEngine)

# CMake parameters
set(CMAKE_CXX_STANDARD 20)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Paths
set(VCPKG_DIR "${CMAKE_SOURCE_DIR}/external/vcpkg")
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# vcpkg
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

find_package(assimp CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

find_path(STB_INCLUDE_DIRS "stb.h")

include_directories(${INC_DIR})

# First party stuff
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_target(copy-assets ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${CMAKE_BINARY_DIR}/assets")
add_custom_target(copy-shader-sources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${SRC_DIR}/GL/Shader/Source" "${CMAKE_BINARY_DIR}/resources/shaders")

add_dependencies(${PROJECT_NAME} copy-assets copy-shader-sources)

target_include_directories(${PROJECT_NAME} PRIVATE ${STB_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
        assimp::assimp
        cxxopts::cxxopts
        fmt::fmt
        glad::glad
        glfw
        glm::glm
        imgui::imgui
        spdlog::spdlog
        -limm32)

target_precompile_headers(
        ${PROJECT_NAME} PRIVATE

        # STL
        <algorithm>
        <utility>
        <memory>

        # Third-party
        <spdlog/spdlog.h>
        <fmt/core.h>
        <glad/glad.h>
        <GLFW/glfw3.h>
)