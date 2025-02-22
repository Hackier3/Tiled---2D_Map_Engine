#include <SFML/Graphics.hpp>
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "hdr/Player.h"
#include "hdr/map.h"

int main()
{
    //sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window", sf::Style::Close);
    //sf::Texture playerTexture;
    //playerTexture.loadFromFile("resources\\graphics\\BODY_skeleton.png");

    //Player player(&playerTexture, sf::Vector2u(9, 3), 0.1f, 150.0f);

    //float deltaTime = 0.0f;
    //sf::Clock clock;
    //window.setFramerateLimit(150);

    //while (window.isOpen()) {
    //    deltaTime = clock.restart().asSeconds();

    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //    }

    //    player.Update(deltaTime);

    //    window.clear(sf::Color(150, 150, 150));
    //    player.Draw(window);
    //    window.display();
    //}

    Map map("resources/maps/obozowisko.tmx");
    map.printInfo();

    return 0;
}