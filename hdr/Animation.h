#pragma once // Zabezpieczenie przed wielokrotnym dołączeniem

#include <SFML/Graphics.hpp>
#include "map.h"
#include "World.h"

class Animation {
public:
    friend class Player;
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();

    unsigned int GetCurrentImageColumn();
    unsigned int GetImageCountColumn();
    sf::IntRect uvRect; // dana reprezentujaca klatke animacji

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;

    void UpdateCharacter(int row, float deltaTime, bool faceRight);
    void UpdateTileInLayer(World& world, float deltaTime);
    void SetCurrentImageColumn(unsigned int xSetter);
};
