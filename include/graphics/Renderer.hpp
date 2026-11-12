#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include <array>

struct RenderBody
{
    glm::vec3 position{0.0f};
    float radius = 1.0f;
    glm::vec3 color{1.0f};
    unsigned detail = 0; 
};
// struct RenderStyle{
//     glm::vec3 color{1.0f};
//     unsigned detail = 0; 
// };

class Renderer
{
public:
    Renderer(unsigned width, unsigned height);
    void init(unsigned width, unsigned height);
    void resize(unsigned width, unsigned height);
    void render(const std::vector<RenderBody>& bodies);
    void shutdown();
    Camera& getCamera() noexcept;

private:
    Shader shader;
    std::array<Mesh,5> spheres; // spheres geometry
    Camera camera;
};