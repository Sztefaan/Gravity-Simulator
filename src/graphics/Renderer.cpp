#include "graphics/Renderer.hpp"
#include <glad/gl.h>
#include <vector>

Renderer::Renderer(unsigned width, unsigned height) : camera(width, height) {}

void Renderer::init(unsigned width, unsigned height)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    shader.load(
        "assets/shaders/triangle.vert",
        "assets/shaders/triangle.frag"
    );

    const std::vector<Vertex> vertices = {
        // Position
         {{-1.0f, 0.0f,  0.0f }}, 
         {{ 1.0f, 0.0f,  0.0f }},
         {{ 0.0f, 1.0f,  0.0f }}
    };
    triangle.init(vertices);

    const Vertex corners[] = {
         {{-1.0f, -1.0f, -1.0f }},
         {{ 1.0f, -1.0f, -1.0f }}, 
         {{ 1.0f,  1.0f, -1.0f }}, 
         {{-1.0f,  1.0f, -1.0f }}, 
         {{-1.0f, -1.0f,  1.0f }}, 
         {{ 1.0f, -1.0f,  1.0f }}, 
         {{ 1.0f,  1.0f,  1.0f }}, 
         {{-1.0f,  1.0f,  1.0f }}
    };

    // Each pair describes one of the cube's twelve edges.
    const unsigned edges[][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    std::vector<Vertex> cubeVertices;
    cubeVertices.reserve(24);
    for (const auto& edge : edges)
    {
        cubeVertices.push_back(corners[edge[0]]);
        cubeVertices.push_back(corners[edge[1]]);
    }
    cube.init(cubeVertices, Mesh::Primitive::Lines);

    resize(width, height);
}

void Renderer::resize(unsigned width, unsigned height)
{
    glViewport(
        0,
        0,
        width,
        height
    );

    camera.resize(width, height);
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());

    shader.setVec3("uColor", glm::vec3(1.f, 0.3f, 0.2f));
    triangle.draw();
    
    shader.setVec3("uColor", glm::vec3(0.3f, 0.8f, 1.f));
    cube.draw();
}

void Renderer::shutdown()
{
    triangle.destroy();
    cube.destroy();
    shader.destroy();
}
Camera& Renderer::getCamera() noexcept{
    return camera;
}