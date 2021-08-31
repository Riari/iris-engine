cmake_minimum_required(VERSION 3.16)
project(IrisEngine)

# CMake parameters
set(CMAKE_CXX_STANDARD 20)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Paths
set(EXT_DIR "${CMAKE_SOURCE_DIR}/external")
set(CXXOPTS_DIR "${EXT_DIR}/cxxopts")
set(FMT_DIR "${EXT_DIR}/fmt")
set(GLAD_DIR "${EXT_DIR}/glad")
set(GLFW_DIR "${EXT_DIR}/glfw")
set(GLM_DIR "${EXT_DIR}/glm")
set(IMGUI_DIR "${EXT_DIR}/imgui")
set(KHR_DIR "${EXT_DIR}/KHR")
set(SPDLOG_DIR "${EXT_DIR}/spdlog")
set(STB_DIR "${EXT_DIR}/stb")
set(VCPKG_DIR "${EXT_DIR}/vcpkg")

set(ZLIB_DIR "${VCPKG_DIR}/packages/zlib_x64-windows")
set(ASSIMP_DIR "${VCPKG_DIR}/packages/assimp_x64-windows")

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# GLM
find_package(glm CONFIG PATHS "${GLM_DIR}/cmake/glm/" REQUIRED)

# GLAD
add_library(glad "${GLAD_DIR}/include/glad/glad.h" "${GLAD_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${KHR_DIR}/include")

# ImGui
set(IMGUI_HEADERS
        "${IMGUI_DIR}/include/imconfig.h"
        "${IMGUI_DIR}/include/imgui.h"
        "${IMGUI_DIR}/include/imgui_impl_glfw.h"
        "${IMGUI_DIR}/include/imgui_impl_opengl3.h"
        "${IMGUI_DIR}/include/imgui_internal.h"
        "${IMGUI_DIR}/include/imstb_rectpack.h"
        "${IMGUI_DIR}/include/imstb_textedit.h"
        "${IMGUI_DIR}/include/imstb_truetype.h"
)

set(IMGUI_SOURCES
        "${IMGUI_DIR}/src/imgui.cpp"
        "${IMGUI_DIR}/src/imgui_demo.cpp"
        "${IMGUI_DIR}/src/imgui_draw.cpp"
        "${IMGUI_DIR}/src/imgui_impl_glfw.cpp"
        "${IMGUI_DIR}/src/imgui_impl_opengl3.cpp"
        "${IMGUI_DIR}/src/imgui_tables.cpp"
        "${IMGUI_DIR}/src/imgui_widgets.cpp"
)

add_library(imgui STATIC "${IMGUI_SOURCES}" "${IMGUI_HEADERS}")

target_compile_definitions(imgui
        PRIVATE
        IMGUI_IMPL_OPENGL_LOADER_GLAD=1
)

target_include_directories(imgui
        PUBLIC
        "${IMGUI_DIR}/include"
        "${GLAD_DIR}/include"
        "${GLFW_DIR}/include"
        "${KHR_DIR}/include"
)

# zlib
set(ZLIB_LIBRARY "${ZLIB_DIR}/lib/zlib.lib")
set(ZLIB_INCLUDE_DIR "${ZLIB_DIR}/include")

# Assimp
find_package(assimp CONFIG REQUIRED)

# Misc. third party stuff
include_directories(
        "${CXXOPTS_DIR}"
        "${GLAD_DIR}/include"
        "${GLM_INCLUDE_DIRS}"
        "${IMGUI_DIR}/include"
        "${ASSIMP_DIR}/include"
        "${INC_DIR}"
        "${STB_DIR}"
)

add_subdirectory(${FMT_DIR})
add_subdirectory(${GLFW_DIR})
add_subdirectory(${SPDLOG_DIR})

# First party stuff
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_target(copy-assets ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${CMAKE_BINARY_DIR}/assets")
add_custom_target(copy-shader-sources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${SRC_DIR}/GL/Shader/Source" "${CMAKE_BINARY_DIR}/resources/shaders")

add_dependencies(${PROJECT_NAME} copy-assets copy-shader-sources)

target_link_libraries(${PROJECT_NAME} PUBLIC fmt glad glfw imgui spdlog assimp::assimp -limm32)

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