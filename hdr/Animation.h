#pragma once

#include <SFML/Graphics.hpp>
#include "World.h"

class World;

class Animation {
public:
    friend class Player;
    friend class World;
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();
    unsigned int GetCurrentImageColumn();
    unsigned int GetImageCountColumn();
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;

    void UpdateCharacter(int row, float deltaTime, bool faceRight);
    static void UpdateLayersTextures(World& world, float deltaTime);
    void SetCurrentImageColumn(unsigned int xSetter);
};
