#include "../hdr/World.h"

World* World::instance = nullptr;

World& World::getInstance(sf::Texture* playerTexture, sf::RenderWindow& window) {
    if (!instance) {
        instance = new World(playerTexture, window);
    }
    return *instance;
}

World::World(sf::Texture* playerTexture, sf::RenderWindow& window)
    : window(window){
    player = new Player(playerTexture, sf::Vector2u(9, 3), 0.1f, 150.0f);
    float windowRatio = float(window.getSize().x) / float(window.getSize().y);
    this->viewHeight = 700;
    this->viewWidth = viewHeight * windowRatio;
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(viewWidth, viewHeight));
    this->view = view;
    this->maps.push_back(Map("resources/maps/obozowisko.tmx"));
}

void World::Draw() {
    view.setCenter(player->GetPosition());
    maps[0].drawUnderground(window);
    player->Draw(window);
    maps[0].drawUpground(window);
    window.display();
    window.clear();
}

void World::Update(float deltaTime) {
    this->deltaTime = deltaTime;
    player->Update(deltaTime);
    this->CenterView();
    this->Draw();
}

void World::CenterView() {
    view.setCenter(player->GetPosition());
    window.setView(view);
}

World::~World() {
    delete player;
}