#pragma once

#include <SFML/Graphics.hpp>

#include "Ball.h"

class Game {
    sf::RenderWindow window;
    Ball ball;
    sf::Font font;
    sf::Text bounceCountDisplay;

public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
};