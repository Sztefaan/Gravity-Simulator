
#pragma once

#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>

class App
{
public:
    App();

    void run();

private:
    void processEvents();
    void update(double dt);
    void render();

    sf::Window window;
    sf::Clock clock;
};
