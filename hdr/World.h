#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"

class Map;
class Player;

class World
{
public:
    friend class Animation;
    static World& getInstance(sf::Texture* playerTexture, sf::RenderWindow& window);
    World(sf::Texture* playerTexture, sf::RenderWindow& window);
    ~World();

    void Update(float deltaTime);

private:
    static World* instance;
    float deltaTime;
    std::vector<Map> maps;
    Player* player;
    sf::RenderWindow& window;
    sf::View view;
    float viewWidth;
    float viewHeight;

    void Draw();
    void CenterView();
    World(const World&) = delete;
    World& operator=(const World&) = delete;
};