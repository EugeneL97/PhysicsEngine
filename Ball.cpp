//
// Created by eugenel on 1/8/25.
//
#include "Ball.h"
#include "constants.h"

Ball::Ball(float x, float y)
    : position{x,y}, velocity{50000.f, 0.f}, bounceCount{0} {
    circle.setRadius(RADIUS);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(position);
}

void Ball::update() {
    velocity += acceleration * DT;
    position += velocity * DT;

    handleVerticalCollision();
    handleHorizontalCollision();

    circle.setPosition(position);
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
        bounceCount += 1;
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
        bounceCount += 1;
    }
}
void Ball::draw(sf::RenderWindow& window) const {
    window.draw(circle);
}

int Ball::getBounceCount() const {
    return bounceCount;
}


