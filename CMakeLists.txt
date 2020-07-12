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

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_library(glad "${GLAD_DIR}/include/glad/glad.h" "${GLAD_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${KHR_DIR}/include")

include_directories("${GLAD_DIR}/include")

add_subdirectory(${GLFW_DIR})
add_subdirectory(${SPDLOG_DIR})

file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SRC_DIR}/GL/Shader/Source" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/shaders"
    COMMENT "Copying shaders" VERBATIM
)

target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}/GL")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad spdlog)