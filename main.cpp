
#include <SFML/Graphics.hpp>

int main() {
    constexpr int WINDOW_WIDTH{800};
    constexpr int WINDOW_HEIGHT{600};
    constexpr int FRAME_RATE_LIMIT{60};
    sf::Vector2f GRAVITY{0, 980.f};
    constexpr float x{400.f};
    constexpr float y{100.f};
    constexpr float radius{20.f};
    constexpr float bounceCoefficient{.98f};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Verlet Integration Test");
    window.setFramerateLimit(FRAME_RATE_LIMIT);

    sf::CircleShape circle(radius);
    circle.setPosition(x, y);
    circle.setFillColor(sf::Color::Red);

    sf::Vector2f currentPosition{x,y};
    sf::Vector2f previousPosition{x,y};
    sf::Vector2f acceleration{GRAVITY};
    sf::Vector2f velocity{0.f, 0.f};
    float dt = 1.f / FRAME_RATE_LIMIT;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        /*sf::Vector2f newPosition = 2.f * currentPosition - previousPosition + acceleration * dt * dt;
        previousPosition = currentPosition;
        currentPosition = newPosition;*/

        velocity += acceleration * dt;
        currentPosition += velocity * dt;


        if (currentPosition.y + circle.getRadius() * 2 >= window.getSize().y) {
            currentPosition.y = window.getSize().y - circle.getRadius() * 2;

            //sf::Vector2f velocity = currentPosition - previousPosition;

            velocity.y = -velocity.y * bounceCoefficient;

            //previousPosition = currentPosition - velocity;

        }

        circle.setPosition(currentPosition);

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}