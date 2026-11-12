
#pragma once

#include <GLFW/glfw3.h>
#include "graphics/Renderer.hpp"
#include "graphics/CameraController.hpp"
#include "physics/Simulation.hpp"
#include <vector>

class App
{
public:
    App();

    void run();
    void onScroll(double yoffset);
    void onResize(int width, int height);
    void onMouseButton(int button, int action);
    void onCursorPos(double x, double y);
private:
    bool drag{false};
    bool firstDrag{true};
    double lastX{0.}, lastY{0.};
    void openGlInit();
    void processInput(double dt);
    void update(double dt);
    void render();

    int appWidth{1920}, appHeight{1080};
    GLFWwindow* window;
    Renderer renderer;
    CameraController cameraController;
    std::vector<RenderBody> renderBodies;
    
    Simulation simulation;
    
};
