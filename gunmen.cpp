#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Inicjalizacja okna SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Map Viewer");

    // Wczytanie mapy TMX
    tmx::Map map;
    if (!map.load("resources/maps/test.tmx")) {
        std::cerr << "Failed to load the TMX map!" << std::endl;
        return -1;
    }

    // Pobranie szerokości i wysokości mapy w kafelkach
    int mapWidth = map.getTileCount().x;    // Liczba kafelków w poziomie
    int mapHeight = map.getTileCount().y;   // Liczba kafelków w pionie
    int tileSize = map.getTileSize().x;     // Rozmiar pojedynczego kafelka (zakładamy kwadratowe kafelki)

    // Wczytanie tilesetów
    std::vector<sf::Texture> textures;
    for (const auto& tileset : map.getTilesets()) {
        sf::Texture texture;
        if (texture.loadFromFile(tileset.getImagePath())) {
            textures.push_back(texture);
        }
        else {
            std::cerr << "Failed to load texture: " << tileset.getImagePath() << std::endl;
        }
    }

    // Iteracja po warstwach i szukanie warstw kafelkowych
    for (const auto& layer : map.getLayers()) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto* tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());

            if (tileLayer) {
                std::cout << "\n\nZnaleziono warstwę: " << tileLayer->getName() << std::endl << std::endl;

                const auto& tiles = tileLayer->getTiles();
                for (size_t i = 0; i < tiles.size(); ++i) {
                    int tileID = tiles[i].ID;

                    // Obliczanie współrzędnych kafelka na mapie
                    int x = (i % mapWidth) ;
                    int y = (i / mapWidth) ;

                    std::cout << "Tile ID: " << tileID << " at (" << x << ", " << y << ")" << std::endl;
                }
            }
        }
    }

    return 0;
}
