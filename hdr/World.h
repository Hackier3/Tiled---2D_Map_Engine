#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Map.h"

class Player;

class World
{
public:
    friend class Animation;
    static World& getInstance(sf::Texture* playerTexture, sf::RenderWindow& window);
    ~World();

    void Update(float deltaTime);

private:
    static World* instance;
    float deltaTime;
    std::vector<Map> maps;
    Player player;
    sf::RenderWindow& window;
    sf::View view;
    float viewWidth;
    float viewHeight;

    World(sf::Texture* playerTexture, sf::RenderWindow& window);
    void Draw();
    void CenterView();

    // Usuwamy możliwość kopiowania i przypisywania
    World(const World&) = delete;
    World& operator=(const World&) = delete;
};
