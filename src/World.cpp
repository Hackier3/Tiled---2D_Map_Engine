#include "../hdr/World.h"

World::World(sf::Texture* playerTexture, sf::RenderWindow& window)
    : window(window),
    player(playerTexture, sf::Vector2u(9, 3), 0.1f, 150.0f)  // Tymczasowa inicjalizacja player
{
    this->maps.push_back(Map("resources/maps/obozowisko.tmx"));
}

void World::Draw() {
    maps[0].drawUnderground(window);
    player.Draw(window);
    maps[0].drawUpground(window);
}

void World::Update(float deltaTime) {
    this->deltaTime = deltaTime;
    player.Update(deltaTime);
    this->Draw();
}

World::~World() {
}