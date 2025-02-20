#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Map.hpp>
#include <SFML/Graphics.hpp>
#include "../hdr/map.h"
#include <iostream>

Map::Map(std::string mapPath)
{
    if (!map.load(mapPath)) {
        throw std::runtime_error("Failed to load the TMX map from path: " + mapPath);
    }

    mapWidth = map.getTileCount().x;
    mapHeight = map.getTileCount().y;
    tileSize = map.getTileSize().x;
    if (!tilesInfo.empty()) {
        setTilesInfo();
    }
    processTileLayers();
}

void Map::setTilesInfo() {
	for (const auto& layer : map.getLayers()) {

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
        std::cout << "----------------------------\n";
    }
}
