
cmake_minimum_required(VERSION 3.22)

project(gravity_simulator LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.1 REQUIRED COMPONENTS Graphics)
find_package(OpenGL REQUIRED)

# GLAD 2
add_library(glad STATIC
    external/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    
    src/App.cpp
    include/App.hpp
    
    src/graphics/Camera.cpp
    src/graphics/CameraController.cpp    
    src/graphics/Renderer.cpp
    src/graphics/Shader.cpp
    src/graphics/Mesh.cpp


    include/graphics/Camera.hpp
    include/graphics/CameraController.hpp
    include/graphics/Renderer.hpp
    include/graphics/Shader.hpp
    include/graphics/Mesh.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Window
    OpenGL::GL
    glad
)

# Add a separate test target once tests/SimulationTests.cpp is implemented.
