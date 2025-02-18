#include <SFML/Graphics.hpp>
#include <iostream>
#include "hdr/Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Close);
    window.setFramerateLimit(150);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("resources/graphics/BODY_skeleton.png")) {
        std::cerr << "Błąd: Nie można załadować tekstury!" << std::endl;
        return -1;
    }

    Player player(&playerTexture, sf::Vector2u(9, 3), 0.1f, 150.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update(deltaTime);

        window.clear(sf::Color(150, 150, 150));
        player.Draw(window);
        window.display();
    }

    return 0;
}
