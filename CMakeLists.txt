
cmake_minimum_required(VERSION 3.22)

project(gravity_simulator LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.1 REQUIRED COMPONENTS Window)
find_package(OpenGL REQUIRED)

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
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Window
    OpenGL::GL
    glad
)