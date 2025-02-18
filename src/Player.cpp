﻿#pragma once
#include <SFML/Graphics.hpp>
#include "../hdr/Animation.h"
#include "../hdr/Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	// obliczamy wysokość proporcjonalnie do tekstury
	float bodyWidth = 80.0f;
	float scaleFactor = bodyWidth / animation.uvRect.width;  // Proporcja szerokości
	float bodyHeight = animation.uvRect.height * scaleFactor;  // Skalowanie wysokości według tej samej proporcji

	body.setSize(sf::Vector2f(bodyWidth, bodyHeight));  // Ustawienie nowych wymiarów
	body.setPosition({ 206.0f, 206.0f });
	body.setTexture(texture);
}

Player::~Player() {
};

void Player::Update(float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);
	moving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		movement.x -= speed * deltaTime;
		faceRight = false;
		moving = true;
		row = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		movement.x += speed * deltaTime;
		faceRight = true;
		moving = true;
		row = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		movement.y -= speed * deltaTime;
		moving = true;
		row = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		movement.y += speed * deltaTime;
		moving = true;
		row = 2;
	}

	if (moving) {
		animation.Update(row, deltaTime, faceRight);
	}
	else {
		static float timeSinceLastChange = 0.0f;
		float changeInterval = 0.55f; // Czas w sekundach między zmianami klatek
		timeSinceLastChange += deltaTime;
			
		if (timeSinceLastChange >= changeInterval) {
			if (animation.getCurrentImageColumn() != animation.getImageCountColumn() - 1) {
				animation.setCurrentImageColumn(animation.getImageCountColumn() - 1);
			}
			else {
				animation.setCurrentImageColumn(0);
			}

			timeSinceLastChange = 0.0f; // Resetowanie czasu po zmianie klatki
			animation.Update(row, 0, faceRight);
		}
	}


	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(body);
}