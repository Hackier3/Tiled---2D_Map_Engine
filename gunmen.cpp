#include <SFML/Graphics.hpp>
#include <iostream>
#include "hdr/Player.h"
#include "hdr/tinyxml2.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window", sf::Style::Close);
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("resources/graphics/BODY_skeleton.png")) {
        std::cerr << "Error loading texture!" << std::endl;
        return -1;
    }
    Player player(&playerTexture, sf::Vector2u(9, 3), 0.1f, 150.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;
    window.setFramerateLimit(150); 

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

    player.Update(deltaTime);

        window.clear(sf::Color(150, 150, 150));
        player.Draw(window);
        window.display();
    }


    tinyxml2::XMLDocument doc;
    return 0;
}