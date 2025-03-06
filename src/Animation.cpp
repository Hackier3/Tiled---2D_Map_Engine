#include "../hdr/Animation.h"
#include <filesystem>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime){
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	sf::Vector2u textureSize = texture->getSize();
	uvRect.width = textureSize.x / float(imageCount.x);
	uvRect.height = textureSize.y / float(imageCount.y);
}

void Animation::UpdateCharacter(int row, float deltaTime, bool faceRight){
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime){
		totalTime = 0;
		currentImage.x++;

		if (currentImage.x >= imageCount.x){
			currentImage.x = 0;
		}
	}
	
	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight) {
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	else {  // odbicie lustrzane postaci
		uvRect.left = currentImage.x * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
}

void Animation::UpdateLayersTextures(World& world, float deltaTime) {
	for (auto& map : world.maps) {
		for (auto& layer : map.layers) {

			for (auto& tile : layer->animatedTiles) {
				// Aktualizacja czasu do zmiany klatki
				std::get<2>(tile.allFramesInfo[tile.recentTile]) -= deltaTime * 1000;

				// Jeśli czas do zmiany klatki się skończył, przechodzimy do następnej
				if (std::get<2>(tile.allFramesInfo[tile.recentTile]) > 0) {
					continue;
				}

				tile.recentTile = (tile.recentTile + 1) % tile.allFramesInfo.size();

				// Ustawienie nowego czasu dla bieżącej klatki
				std::get<2>(tile.allFramesInfo[tile.recentTile]) = std::get<1>(tile.allFramesInfo[tile.recentTile]);

				int newTileID = std::get<0>(tile.allFramesInfo[tile.recentTile]);
				auto it = map.tilesInfo.find(newTileID);

				if (it != map.tilesInfo.end()) {
					sf::Texture newTexture;
					if (!newTexture.loadFromFile(it->second.path)) {
						throw std::runtime_error("Failed to load texture" + it->second.path);
					}

					sf::RectangleShape clearRect(sf::Vector2f(newTexture.getSize().x, newTexture.getSize().y));
					clearRect.setPosition(tile.x * map.tileSize, tile.y * map.tileSize);
					clearRect.setFillColor(sf::Color::Transparent);

					sf::RenderStates states;
					states.blendMode = sf::BlendNone; // Tryb mieszania: zastąp piksele
					layer->canvasTexture.draw(clearRect, states);

					sf::Sprite sprite(newTexture);
					sprite.setPosition(tile.x * map.tileSize, tile.y * map.tileSize);
					layer->canvasTexture.draw(sprite);
					layer->canvasTexture.display();

					layer->canvasTexture.display();
					layer->sprite.setTexture(layer->canvasTexture.getTexture());
				}
			}
		}
	}
}



void Animation::SetCurrentImageColumn(unsigned int xSetter) {
	currentImage.x = xSetter;
}

unsigned int Animation::GetCurrentImageColumn() {
	return currentImage.x;
}

unsigned int Animation::GetImageCountColumn() {
	return imageCount.x;
}

Animation::~Animation() {}
