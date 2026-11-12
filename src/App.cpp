
#include "App.hpp"

#include <glad/gl.h>
#include <algorithm>
#include <stdexcept>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) return;

    glViewport(0, 0, width, height);

    if (auto* app = static_cast<App*>(glfwGetWindowUserPointer(window)))
        app->onResize(width, height);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (auto* app = static_cast<App*>(glfwGetWindowUserPointer(window)))
        app->onMouseButton(button, action);
}

void cursor_pos_callback(GLFWwindow* window, double x, double y)
{
    if (auto* app = static_cast<App*>(glfwGetWindowUserPointer(window)))
        app->onCursorPos(x, y);
}

void App::onMouseButton(int button, int action)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT) return;

    if (action == GLFW_PRESS)
    {
        drag = true;
        firstDrag = true;
    }
    else if (action == GLFW_RELEASE)
    {
        drag = false;
    }
}

void App::onCursorPos(double x, double y)
{
    if (!drag) return;

    if (firstDrag)
    {
        lastX = x;
        lastY = y;
        firstDrag = false;
        return;
    }

    constexpr float sensitivity = 0.005f;
    float dx = static_cast<float>(x - lastX);
    float dy = static_cast<float>(y - lastY);
    lastX = x;
    lastY = y;

    cameraController.changeAngle(dx * sensitivity, dy * sensitivity);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (auto* app = static_cast<App*>(glfwGetWindowUserPointer(window)))
        app->onScroll(yoffset);
}

void App::onScroll(double yoffset)
{
    cameraController.changeDistance(static_cast<float>(std::pow(1.1, -yoffset)));
}

void App::onResize(int width, int height)
{
    renderer.getCamera().resize(width, height);
}


void App::openGlInit(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
}

App::App() : renderer(appWidth, appHeight), cameraController(renderer.getCamera()){
    openGlInit();
    window = glfwCreateWindow(appWidth, appHeight, "Gravity simulator", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw(std::runtime_error("Failed to create GLFW window"));
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);   
    if(!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))){
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll_callback);
    renderer.init(appWidth, appHeight);
    
    for (unsigned i = 0; i < 5; ++i) // temporary RenderBody generation for testing purposes 
    {
        RenderBody b;
        b.position = glm::vec3(-5.0f + i * 2.5f, 0.0f, 0.0f);
        b.radius   = 1.0f;
        b.color    = glm::vec3((i + 1) * 0.2f);
        b.detail      = i;
        renderBodies.push_back(b);
    }

}
void App::run()
{
    constexpr double fixedDt = 1.0 / 120.0;
    constexpr double maxFrameTime = 0.25;

    double accumulator = 0.0;
    double previous = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double frameTime = glfwGetTime();
        frameTime = std::min(frameTime - previous, maxFrameTime);
        previous = glfwGetTime();
        accumulator += frameTime;

        processInput(frameTime);

        while (accumulator >= fixedDt)
        {
            update(fixedDt);
            accumulator -= fixedDt;
        }

        render();
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    renderer.shutdown();
    glfwTerminate();
}

void App::processInput(double dt)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

    glm::vec3 dir(0.f);
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)
        dir.z += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)
        dir.z -= 1.0f;
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)
        dir.x += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
        dir.x -= 1.0f;
    if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS)
        dir.y += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)==GLFW_PRESS)
        dir.y -= 1.0f;
    cameraController.moveTarget(dir, static_cast<float>(dt));

}

void App::update([[maybe_unused]] double dt)
{
    simulation.step(dt);
}

void App::render()
{
    renderer.render(renderBodies);
    glfwSwapBuffers(window);
}

