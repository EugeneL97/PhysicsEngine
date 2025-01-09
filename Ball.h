#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Ball {
private:
    sf::CircleShape circle;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration{0.f, 980.f};

    static constexpr float RADIUS{20.f};
    static constexpr float BOUNCE_COEFFICIENT{.5f};
    static constexpr float FRICTION_COEFFICIENT{.01f};

    // Due to gravity acting down on the force + delta time (with the framerate)
    static constexpr float GRAVITY_THRESHOLD{11.0f};

public:
    Ball(float x, float y);
    void update(std::vector<Ball>& balls);
    void readInput();
    void handleBallCollision(std::vector<Ball>& balls);
    void handleVerticalCollision();
    void handleHorizontalCollision();
    void draw(sf::RenderWindow& window) const;

    float getRadius();
    float dot(const sf::Vector2f& a, const sf::Vector2f& b);
};