#include "graphics/Renderer.hpp"
#include <glad/gl.h>
#include <vector>

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
        // Position              Color
        {{-0.8f, -0.6f,  1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.8f, -0.6f,  0.0f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.0f,  0.8f, -1.0f}, {0.0f, 0.0f, 1.0f}}
    };

    triangle.init(vertices);

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

    shader.setMat4("uView", camera.getView());
    shader.setMat4("uProjection", camera.getProjection());

    triangle.draw();
}

void Renderer::shutdown()
{
    triangle.destroy();
    shader.destroy();
}