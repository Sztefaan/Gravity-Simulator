#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class Renderer
{
public:
    Renderer(unsigned width, unsigned height);
    void init(unsigned width, unsigned height);
    void resize(unsigned width, unsigned height);
    void render();
    void shutdown();

private:
    Shader shader;
    Mesh triangle;
    Mesh cube;
    Camera camera;
};