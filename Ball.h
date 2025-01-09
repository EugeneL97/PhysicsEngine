#pragma once

#include <SFML/Graphics.hpp>

class Ball {
    sf::CircleShape circle;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration{0.f, 980.f};
    int bounceCount;
    static constexpr float RADIUS{20.f};
    static constexpr float BOUNCE_COEFFICIENT{.5f};
    static constexpr float FRICTION_COEFFICIENT{.01f};

    // Due to gravity acting down on the force + delta time (with the framerate)
    static constexpr float GRAVITY_THRESHOLD{11.0f};

public:
    Ball(float x, float y);
    void update();
    void handleVerticalCollision();
    void handleHorizontalCollision();
    void draw(sf::RenderWindow& window) const;
    int getBounceCount()const;

};