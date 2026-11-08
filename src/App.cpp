
#include "App.hpp"

#include <glad/gl.h>
#include <algorithm>
#include <stdexcept>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) return;
    
    glViewport(0, 0, width, height);

    auto* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera)
        camera->resize(width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    // float xpos = static_cast<float>(xposIn);
    // float ypos = static_cast<float>(yposIn);

    // if (firstMouse)
    // {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }

    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    // lastX = xpos;
    // lastY = ypos;

//    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(static_cast<float>(yoffset));
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
    if(!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))){
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    renderer.init(appWidth, appHeight);
    
    for (unsigned i = 0; i < 5; ++i)
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
    
    while (!glfwWindowShouldClose(window))
    {
        double frameTime = glfwGetTime();
        frameTime = std::min(frameTime, maxFrameTime);

        accumulator += frameTime;

        processInput();

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

void App::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

}

void App::update([[maybe_unused]] double dt)
{
    // TODO: Advance Simulation by dt
}

void App::render()
{
    renderer.render(renderBodies);
    glfwSwapBuffers(window);
}

