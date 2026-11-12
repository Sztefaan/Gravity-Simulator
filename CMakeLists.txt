
cmake_minimum_required(VERSION 3.22)

project(gravity_simulator LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.10
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm)

# OpenGL
find_package(OpenGL REQUIRED)

add_library(glad STATIC
    external/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
)

# Application
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/App.cpp

    src/graphics/Camera.cpp
    src/graphics/CameraController.cpp
    src/graphics/Renderer.cpp
    src/graphics/Shader.cpp
    src/graphics/Mesh.cpp

    include/App.hpp
    include/graphics/Camera.hpp
    include/graphics/CameraController.hpp
    include/graphics/Renderer.hpp
    include/graphics/Shader.hpp
    include/graphics/MeshGenerator.hpp
    src/graphics/MeshGenerator.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Required compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    GLFW_INCLUDE_NONE
    GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
    glad
    glm::glm
)
