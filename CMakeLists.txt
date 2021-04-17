cmake_minimum_required(VERSION 3.16)
project(IrisEngine)

set(CMAKE_CXX_STANDARD 20)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(EXT_DIR "${CMAKE_SOURCE_DIR}/external")
set(CXXOPTS_DIR "${EXT_DIR}/cxxopts")
set(FMT_DIR "${EXT_DIR}/fmt")
set(GLAD_DIR "${EXT_DIR}/glad")
set(GLFW_DIR "${EXT_DIR}/glfw")
set(GLM_DIR "${EXT_DIR}/glm")
set(KHR_DIR "${EXT_DIR}/KHR")
set(SPDLOG_DIR "${EXT_DIR}/spdlog")
set(STB_DIR "${EXT_DIR}/stb")

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(glm CONFIG PATHS "${GLM_DIR}/cmake/glm/" REQUIRED)

add_library(glad "${GLAD_DIR}/include/glad/glad.h" "${GLAD_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${KHR_DIR}/include")

include_directories(
        "${CXXOPTS_DIR}"
        "${GLAD_DIR}/include"
        "${GLM_INCLUDE_DIRS}"
        "${INC_DIR}"
        "${STB_DIR}"
)

add_subdirectory(${FMT_DIR})
add_subdirectory(${GLFW_DIR})
add_subdirectory(${SPDLOG_DIR})

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_target(copy-assets ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${CMAKE_BINARY_DIR}/assets")
add_custom_target(copy-shader-sources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${SRC_DIR}/GL/Shader/Source" "${CMAKE_BINARY_DIR}/resources/shaders")

add_dependencies(${PROJECT_NAME} copy-assets copy-shader-sources)

target_link_libraries(${PROJECT_NAME} PUBLIC fmt glad glfw spdlog)

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