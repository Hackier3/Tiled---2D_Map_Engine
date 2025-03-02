#include <SFML/Graphics.hpp>
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "hdr/Player.h"
#include "hdr/map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window", sf::Style::Close);
    sf::Texture playerTexture;
    Map map("resources/maps/obozowisko.tmx");

    playerTexture.loadFromFile("resources\\graphics\\BODY_skeleton.png");
    Player player(&playerTexture, sf::Vector2u(9, 3), 0.1f, 150.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;
    window.setFramerateLimit(150);

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update(deltaTime);

        map.drawMap(window);
        player.Draw(window);
        window.display();
        window.clear();
    }

    return 0;
}

//    Map map("resources/maps/obozowisko.tmx");
//    map.printInfo();
//
//    const int GRID_SIZE = 30;
//    const int TILE_SIZE = 32;
//    std::vector<std::vector<sf::Texture*>> grid(GRID_SIZE, std::vector<sf::Texture*>(GRID_SIZE));
//
//    // Tworzymy renderTexture dla całej siatki
//    sf::RenderTexture renderTexture;
//    renderTexture.create(GRID_SIZE * TILE_SIZE, GRID_SIZE * TILE_SIZE);
//    renderTexture.clear(sf::Color::Transparent);
//
//    // Rysujemy każdą teksturę w siatce
//    for (int y = 0; y < GRID_SIZE; y++) {
//        for (int x = 0; x < GRID_SIZE; x++) {
//            // Wczytujemy tekstury (dla przykładu tylko 2)
//            sf::Texture texture1, texture2;
//            if (!texture1.loadFromFile("tile1.png") || !texture2.loadFromFile("tile2.png")) {
//                std::cerr << "Błąd ładowania tekstur!\n";
//                return -1;
//            }
//
//            sf::Sprite sprite(*grid[y][x]); // Tworzymy sprite'a
//            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE); // Ustawiamy pozycję
//            renderTexture.draw(sprite); // Rysujemy
//        }
//    }
//
//    renderTexture.display(); // Finalizujemy teksturę
//    sf::Texture finalTexture = renderTexture.getTexture();
//    sf::Sprite finalSprite(finalTexture);
//
//    // Tworzymy okno
//    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * TILE_SIZE, GRID_SIZE * TILE_SIZE), "Merged Grid Texture");
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(finalSprite);
//        window.display();
//    }
//
//    return 0;
//}