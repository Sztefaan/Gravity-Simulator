#include "graphics/Renderer.hpp"
#include "graphics/MeshGenerator.hpp"

#include <vector>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(unsigned width, unsigned height) : camera(width, height) {}

void Renderer::init(unsigned width, unsigned height)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    shader.load(
        "assets/shaders/sphere.vert",
        "assets/shaders/sphere.frag"
    );

    spheres[0] = MeshGenerator::generateSphere(1, 12, 6);
    spheres[1] = MeshGenerator::generateSphere(1, 24, 12);
    spheres[2] = MeshGenerator::generateSphere(1, 36, 18);
    spheres[3] = MeshGenerator::generateSphere(1, 64, 32);
    spheres[4] = MeshGenerator::generateSphere(1, 128, 64);
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

void Renderer::render(const std::vector<RenderBody>& bodies)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());

    for (const auto& b : bodies)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), b.position);
        model = glm::scale(model, glm::vec3(b.radius));

        shader.setMat4("uModel", model);
        shader.setVec3("uColor", b.color);
        spheres[b.detail].draw();
    }
}

void Renderer::shutdown()
{
    for(auto& x : spheres){
        x.destroy();
    }
    shader.destroy();
}
Camera& Renderer::getCamera() noexcept{
    return camera;
}