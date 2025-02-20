#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>

#include <iostream>
#include <vector>

std::string getTexturePathForTile(const tmx::Map& map, uint32_t tileID, int& tileX, int& tileY, bool& hasTexture) {
    tileX = 0;
    tileY = 0;
    hasTexture = false;

    if (tileID == 0) {
        return "Empty tile (no texture)";
    }

    for (const auto& tileset : map.getTilesets()) {
        uint32_t firstGID = tileset.getFirstGID();
        uint32_t lastGID = firstGID + tileset.getTileCount() - 1;

        if (tileID >= firstGID && tileID <= lastGID) {
            uint32_t localTileID = tileID - firstGID;

            for (const auto& tile : tileset.getTiles()) {
                if (tile.ID == localTileID && !tile.imagePath.empty()) {
                    hasTexture = true;
                    return tile.imagePath;
                }
            }
        }
    }

    return "Unknown texture (tileID out of range)";
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Map Viewer");

    tmx::Map map;
    if (!map.load("resources/maps/obozowisko.tmx")) {
        std::cerr << "Failed to load the TMX map!" << std::endl;
        return -1;
    }

    // Pobranie szerokości i wysokości mapy w kafelkach
    int mapWidth = map.getTileCount().x;    // Liczba kafelków w poziomie
    int mapHeight = map.getTileCount().y;   // Liczba kafelków w pionie
    int tileSize = map.getTileSize().x;     // Rozmiar pojedynczego kafelka (zakładamy kwadratowe kafelki)

    // Iteracja po warstwach i szukanie warstw kafelkowych
    for (const auto& layer : map.getLayers()) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto* tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());

            if (tileLayer) {
                std::cout << "\n\nZnaleziono warstwe: " << tileLayer->getName() << std::endl << std::endl;

                const auto& tiles = tileLayer->getTiles();
                for (size_t i = 0; i < tiles.size(); ++i) {
                    uint32_t tileID = tiles[i].ID;

                    // Pomijanie pustych kafelków
                    if (tileID == 0) {
                        continue;
                    }

                    // Obliczanie współrzędnych kafelka na mapie
                    int x = (i % mapWidth) * tileSize;
                    int y = (i / mapWidth) * tileSize;

                    std::cout << "Tile ID: " << tileID << " at (" << x << ", " << y << ")";

                    // Znajdź ścieżkę tekstury i pozycję kafelka w teksturze
                    int tileX, tileY;
                    bool hasTexture;
                    std::string texturePath = getTexturePathForTile(map, tileID, tileX, tileY, hasTexture);
                    std::cout << " - Texture: " << texturePath;

                    // Drukowanie pozycji kafelka w teksturze tylko jeśli kafelek ma teksturę
                    if (hasTexture) {
                        std::cout << " - Tile position in texture: (" << tileX << ", " << tileY << ")";
                    }

                    std::cout << std::endl;
                }
            }
        }
    }

    return 0;
}