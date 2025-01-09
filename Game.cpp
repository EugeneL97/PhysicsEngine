//
// Created by eugenel on 1/8/25.
//
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Ball.h"
#include "constants.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Verlet Integration Test"){
    window.setFramerateLimit(FRAME_RATE);

    for (int i = 0; i < 5; ++i) {
        balls.emplace_back(WINDOW_WIDTH / 2 + i, 100.f * i);
    }

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
    for (auto& ball : balls) {
        ball.update(balls);
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    for (const auto& ball : balls) {
        ball.draw(window);
    }
    window.display();
}

