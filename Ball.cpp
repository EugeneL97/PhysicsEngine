//
// Created by eugenel on 1/8/25.
//
#include "Ball.h"
#include <cmath>
#include "constants.h"

Ball::Ball(float x, float y)
    : position{x,y}, velocity{0.f, 0.f} {
    circle.setRadius(RADIUS);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(position);
}


void Ball::update(std::vector<Ball>& balls) {
    velocity += acceleration * DT;
    position += velocity * DT;

    readInput();
    handleBallCollision(balls);
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

void Ball::handleBallCollision(std::vector<Ball>& balls) {
    for (size_t i = 0; i < balls.size(); ++i){
        for (size_t j = i + 1; j < balls.size(); ++j) {
            sf::Vector2f diff = balls[j].position - balls[i].position;
            float dist = std::hypot(diff.x, diff.y);
            float radiusSum = balls[i].getRadius() + balls[j].getRadius();
            //TODO
            //THIS IS ALL FUCKED!!!! We enter this if statement but the collisions are not applying
            if (dist <= radiusSum) {
                sf::Vector2f normal = diff / dist;
                float vA_normal = dot(balls[i].velocity, normal);
                float vB_normal = dot(balls[j].velocity , normal);

                sf::Vector2f vA_new = vA_normal * normal;
                sf::Vector2f vB_new = vB_normal * normal;

                balls[i].velocity += vB_new - vA_new;
                balls[j].velocity += vA_new - vB_new;

                float overlap = radiusSum - dist;
                sf::Vector2f correction = normal * (overlap / 2.0f);

                balls[i].position -= correction;
                balls[j].position += correction;
            }
        }
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

float Ball::getRadius() {
    return RADIUS;
}

float Ball::dot(const sf::Vector2f& a, const sf::Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}