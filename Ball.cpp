//
// Created by eugenel on 1/8/25.
//
#include "Ball.h"
#include "constants.h"

Ball::Ball(float x, float y)
    : position{x,y}, velocity{0.f, 0.f} {
    circle.setRadius(RADIUS);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(position);
}


void Ball::update() {
    velocity += acceleration * DT;
    position += velocity * DT;

    readInput();
    handleVerticalCollision();
    handleHorizontalCollision();

    circle.setPosition(position);
}
void Ball::readInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed((sf::Keyboard::W))) {
        velocity.y += -(position.x + position.y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed((sf::Keyboard::S))) {
        velocity.y += position.x + position.y;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed((sf::Keyboard::A))) {
        velocity.x += -(position.x + position.y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed((sf::Keyboard::D))) {
        velocity.x += position.x + position.y;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        velocity = {0.f, 0.f};
    }

}
void Ball::handleVerticalCollision() {
    float currentY = position.y + circle.getRadius() * 2;
    if (currentY > WINDOW_HEIGHT || position.y < 0) {
        if (currentY > WINDOW_HEIGHT) {
            position.y = WINDOW_HEIGHT - circle.getRadius() * 2;

            if (std::abs(velocity.y) < GRAVITY_THRESHOLD) {
                velocity.x *= (1 - FRICTION_COEFFICIENT);

                if (std::abs(velocity.x) < 0.1f) {
                    velocity.x = 0.f;
                }
            }
        }
        else {
            position.y = 0;
        }
        velocity.y = -velocity.y * BOUNCE_COEFFICIENT;
    }
}

void Ball::handleHorizontalCollision() {
    float currentX = position.x + circle.getRadius() * 2;

    if (currentX > WINDOW_WIDTH || position.x < 0) {

        if (currentX > WINDOW_WIDTH) {
            position.x = WINDOW_WIDTH - circle.getRadius() * 2;
        }
        else {
            position.x = 0;
        }
        velocity.x = -velocity.x * BOUNCE_COEFFICIENT;
    }
}
void Ball::draw(sf::RenderWindow& window) const {
    window.draw(circle);
}


