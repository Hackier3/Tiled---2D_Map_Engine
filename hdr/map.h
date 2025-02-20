#pragma once
#include <tmxlite/Map.hpp>

class Map
{
public:
	Map(std::string mapPath);
	void printInfo();

private:
	tmx::Map map;
	int mapWidth;
	int mapHeight;
	int tileSize;

	struct Tile {
		int GID;
		int firstGID;
		int ID;
		std::string path;
		bool hasAnimation;
		bool hasHitbox;
		bool isFromTileSet;
	};
	static std::map<uint32_t, Tile> tilesInfo;

	struct Layer {
		short int id;
		std::string name;
		std::vector<Tile> tiles;
		std::vector<std::pair<int, int>> coordinates;
	};
	std::vector<Layer> layers; // Pierwsze wchodzą najgłębsze

	void processTileLayers();
	std::string getTexturePathForTile(uint32_t tileID);
	void setTilesInfo();
};

