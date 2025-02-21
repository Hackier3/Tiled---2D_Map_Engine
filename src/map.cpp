#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Map.hpp>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
#include <iostream>

#include "../hdr/map.h"
#include <iomanip>

std::map<uint32_t, Map::Tile> Map::tilesInfo;

Map::Map(std::string mapPath)
{
    tmx::Map map;
    if (!map.load(mapPath) || !doc.load_file(mapPath.c_str())) {
        throw std::runtime_error("Failed to load the TMX map from path: " + mapPath);
    }

    mapWidth = map.getTileCount().x;
    mapHeight = map.getTileCount().y;
    tileSize = map.getTileSize().x;
    if (tilesInfo.empty()) {
        setTilesInfo();
    }
    //processTileLayers();
}

void Map::setTilesInfo() {
    // Przechodzimy przez wszystkie <tileset>
    for (pugi::xml_node tileset : doc.child("map").children("tileset")) {
        int firstGID = tileset.attribute("firstgid").as_int();
        std::string tilesetName = tileset.attribute("name").as_string();

        // Sprawdź, czy w tilesecie są <tile> z <image>
        for (pugi::xml_node tile : tileset.children("tile")) {
            int tileID = tile.attribute("id").as_int();
            pugi::xml_node image = tile.child("image");

            if (image) {
                // Pierwszy raz znaleźliśmy pasujący tileset, więc go wypisujemy
                std::cout << " Tileset: " << tilesetName << " (firstGID = " << firstGID << ")\n";
                std::cout << "-----------------------------------------------------\n";

                std::string imagePath = image.attribute("source").as_string();
                int width = image.attribute("width").as_int();
                int height = image.attribute("height").as_int();

                // Wypisz informacje o kafelku
                std::cout << " Tile ID: " << std::setw(3) << tileID << " | Obraz: " << imagePath
                    << " (" << width << "x" << height << ")\n";

                // Tworzymy nowy obiekt Tile i zapisujemy go w tilesInfo
                Tile newTile;
                newTile.GID = firstGID + tileID;
                newTile.firstGID = firstGID;
                newTile.ID = tileID;
                newTile.path = imagePath;
                newTile.hasAnimation = (tile.child("animation") != nullptr);
                newTile.hasHitbox = (tile.child("objectgroup") != nullptr);
                newTile.isFromTileSet = true;

                // Dodajemy kafelek do mapy
                tilesInfo[newTile.GID] = newTile;
            }
        }

        std::cout << "-----------------------------------------------------\n\n";
    }
}


void Map::printInfo() {
    for (const auto& entry : tilesInfo)
    {
        std::cout << "Tile ID: " << entry.first << "\n";
        std::cout << "Path: " << entry.second.path << "\n";
        std::cout << "Has Animation: " << (entry.second.hasAnimation ? "Yes" : "No") << "\n";
        std::cout << "Has Hitbox: " << (entry.second.hasHitbox ? "Yes" : "No") << "\n";
        std::cout << "Is From TileSet: " << (entry.second.isFromTileSet ? "Yes" : "No") << "\n";
        std::cout << "-----------------------------------------------------\n";
    }
}

Map::~Map() {
}