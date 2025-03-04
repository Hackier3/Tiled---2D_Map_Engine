#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"

class World
{
public:
    World(sf::Texture* playerTexture, sf::RenderWindow& window);
    ~World();

    void Update(float deltaTime);

private:
    float deltaTime;
    std::vector<Map> maps;
    Player player;
    sf::RenderWindow& window;
    sf::View view;
    float viewWidth;
    float viewHeight;

    void Draw();
    void CenterView();
};