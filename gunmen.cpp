#include <SFML/Graphics.hpp>
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "hdr/Player.h"
#include "hdr/Map.h"
#include "hdr/World.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1200, 1000 }), "My window", sf::Style::Close);
    sf::Texture playerTexture;
	playerTexture.loadFromFile("resources/graphics/BODY_skeleton.png");
    World world(&playerTexture, window);

    sf::Clock clock;
    window.setFramerateLimit(150);

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Update(deltaTime);
    }

    return 0;
}