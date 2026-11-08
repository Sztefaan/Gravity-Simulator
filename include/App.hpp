
#pragma once

#include <GLFW/glfw3.h>
#include "graphics/Renderer.hpp"
#include "graphics/CameraController.hpp"
#include <vector>

class App
{
public:
    App();

    void run();
private:
    void openGlInit();
    void processInput();
    void update(double dt);
    void render();

    int appWidth{1920}, appHeight{1080};
    GLFWwindow* window;
    Renderer renderer;
    CameraController cameraController;
    std::vector<RenderBody> renderBodies;
};
