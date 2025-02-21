#pragma once
#include <tmxlite/Map.hpp>
#include <pugixml.hpp>

class Map
{
private:
	int mapWidth;
	int mapHeight;
	int tileSize;
	pugi::xml_document doc;

	struct Tile {
		int GID;
		int firstGID;
		int ID;
		std::string path;
		bool hasAnimation;
		bool hasHitbox;
		bool isFromTileSet;
	};

	struct Layer {
		short int id;
		std::string name;
		std::vector<Tile> tiles;
		std::vector<std::pair<int, int>> coordinates;
	};
	std::vector<Layer> layers; // Pierwsze wchodzą najgłębsze

	//void processTileLayers();
	//std::string getTexturePathForTile(uint32_t tileID);
	void setTilesInfo();

public:
	Map(std::string mapPath);
	~Map();
	void printInfo();
	static std::map<uint32_t, Tile> tilesInfo;


};

