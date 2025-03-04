#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player {
public :
	friend class World;
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	bool moving;
	float bodyWidth;
	float spawnXCord;
	float spawnYCord;

	sf::Vector2f GetPosition();
};