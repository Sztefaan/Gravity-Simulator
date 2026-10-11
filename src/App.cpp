
#include "App.hpp"

#include <glad/gl.h>
#include <algorithm>
#include <stdexcept>

static sf::ContextSettings createContextSettings()
{
    sf::ContextSettings settings;

    settings.majorVersion = 4;
    settings.minorVersion = 0;
    settings.attributeFlags = sf::ContextSettings::Core;
    settings.depthBits = 24;
    settings.stencilBits = 8;   

    return settings;
}


App::App()
    : window(
        sf::VideoMode({800, 600}),
        "Gravity simulator",
        sf::Style::Default,
        sf::State::Windowed,
        createContextSettings()
    )
{
    if (!window.setActive(true))
        throw std::runtime_error("Failed to activate OpenGL context");

    if (!gladLoadGL(sf::Context::getFunction) ||
        !GLAD_GL_VERSION_4_0)
        throw std::runtime_error("OpenGL 4.0 unavailable");

    window.setFramerateLimit(60);

    const auto size = window.getSize();
    glViewport(0, 0, size.x, size.y);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.15f, 1.f);
}

void App::run()
{
    constexpr double fixedDt = 1.0 / 120.0;
    constexpr double maxFrameTime = 0.25;

    double accumulator = 0.0;
    clock.restart();

    while (window.isOpen())
    {
        double frameTime = static_cast<double>(clock.restart().asMicroseconds()) / 1'000'000.0;
        frameTime = std::min(frameTime, maxFrameTime);

        accumulator += frameTime;

        processEvents();

        if (!window.isOpen())
            break;

        while (accumulator >= fixedDt)
        {
            update(fixedDt);
            accumulator -= fixedDt;
        }

        render();
    }
}

void App::processEvents()
{
    while (auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
            
        if (const auto* resized = event->getIf<sf::Event::Resized>())
        {
            glViewport(0, 0, resized->size.x, resized->size.y);
        }
        
        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            switch(key->code){
                case sf::Keyboard::Key::Escape:{
                    window.close();
                    break;
                }
                default:
                    break; 
            }
        }
    }
}

void App::update(double dt) // executes physics engine update (TODO)
{
    
}

void App::render() // executes renderer update (TODO)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    window.display();
}
