#pragma once

#include <SFML/Graphics.hpp>

#include "Ball.h"

class Game {
    sf::RenderWindow window;
    std::vector<Ball> balls;
public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
};