#pragma once // Zabezpieczenie przed wielokrotnym dołączeniem

#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();

    void Update(int row, float deltaTime, bool faceRight);
    void setCurrentImageColumn(unsigned int xSetter);
    unsigned int getCurrentImageColumn();
    unsigned int getImageCountColumn();
    sf::IntRect uvRect;


private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;
};
