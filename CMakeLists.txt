cmake_minimum_required(VERSION 3.16)
project(IrisEngine)

# CMake parameters
set(CMAKE_CXX_STANDARD 20)
set(CXX_FLAGS "-Wall")

# Paths
set(EXT_DIR "${CMAKE_SOURCE_DIR}/external")
set(FLECS_DIR "${EXT_DIR}/flecs")
set(VCPKG_DIR "${EXT_DIR}/vcpkg")
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
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

# First party stuff
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} "${FLECS_DIR}/flecs.c")

add_custom_target(copy-assets ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${CMAKE_BINARY_DIR}/assets")
add_dependencies(${PROJECT_NAME} copy-assets)

target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR} ${STB_INCLUDE_DIRS} ${FLECS_DIR})

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        assimp::assimp
        cxxopts::cxxopts
        fmt::fmt
        glad::glad
        glfw
        glm::glm
        imgui::imgui
        spdlog::spdlog
)
