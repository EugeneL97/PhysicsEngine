//
// Created by eugenel on 1/8/25.
//
#include <SFML/Graphics.hpp>
#include <string>

#include "Game.h"
#include "constants.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Verlet Integration Test"), ball(WINDOW_WIDTH / 2, 100.f){
    window.setFramerateLimit(FRAME_RATE);

    bounceCountDisplay.setCharacterSize(24);
    bounceCountDisplay.setFillColor(sf::Color::White);
    bounceCountDisplay.setPosition(100,100);
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
void Game::update() {
    ball.update();
    bounceCountDisplay.setString("Bounces: " + std::to_string(ball.getBounceCount()));
}

void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(bounceCountDisplay);
    ball.draw(window);
    window.display();
}

