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

				// Aktualizacja pozostałego czasu klatki
				tile.framesInfo[tile.recentTile].second -= deltaTime * 1000;

                // Pomin jesli czas klatki animacji sie nie skonczyl
                if (tile.framesInfo[tile.recentTile].second > 0) {
                    continue;
                }

				tile.framesInfo[tile.recentTile].second = tile.framesInfo[tile.recentTile].first; // reset czasu trwania klatki
				tile.recentTile = (tile.recentTile + 1) % tile.framesInfo.size(); // zmiana indexowania klatki kafelka
				
				sf::RectangleShape clearRect(sf::Vector2f(tile.frameTextures[tile.recentTile].getSize().x, 
														  tile.frameTextures[tile.recentTile].getSize().y));
				clearRect.setPosition(tile.frameSprites[tile.recentTile].getPosition());
				clearRect.setOrigin(tile.frameSprites[tile.recentTile].getOrigin());
				clearRect.setFillColor(sf::Color::Transparent);

				sf::RenderStates states;
				states.blendMode = sf::BlendNone; // Tryb mieszania: zastąp piksele
				layer->canvasTexture.draw(clearRect, states);

				layer->canvasTexture.draw(tile.frameSprites[0]);
				layer->canvasTexture.display();
				layer->sprite.setTexture(layer->canvasTexture.getTexture());
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
