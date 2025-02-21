#pragma once
#include <tmxlite/Map.hpp>
#include <pugixml.hpp>
#include <variant>
#include <vector>
#include <utility> 
#include <sstream> 

class Map
{
private:
	int mapWidth;
	int mapHeight;
	int tileSize;
	pugi::xml_document doc;

	struct Hitbox {
		enum class Type {
			Rectangle,
			Circle,
			Polygon,
			Point
		};

		Type type;
		int x, y; // Pozycja (lewy górny róg dla prostokąta, środek dla koła, punkt odniesienia dla wielokąta/punktu)

		std::variant<
			std::pair<int, int>, // Rectangle: width, height
			int,                 // Circle: radius
			std::vector<std::pair<int, int>>, // Polygon: points
			std::monostate       // Point: brak dodatkowych danych
		> data;

		// Konstruktor domyślny
		Hitbox() : type(Type::Rectangle), x(0), y(0), data(std::make_pair(0, 0)) {}

		Hitbox(int x, int y, int width, int height)
			: type(Type::Rectangle), x(x), y(y), data(std::make_pair(width, height)) {
		}

		Hitbox(int x, int y, int radius)
			: type(Type::Circle), x(x), y(y), data(radius) {
		}

		Hitbox(int x, int y, const std::vector<std::pair<int, int>>& points)
			: type(Type::Polygon), x(x), y(y), data(points) {
		}

		Hitbox(int x, int y)
			: type(Type::Point), x(x), y(y), data(std::monostate{}) {
		}
	};

	using AnimatedData = std::vector<std::pair<int, int>>; // <frameID, duration>
	using TileProperty = std::variant<std::vector<Hitbox>, AnimatedData>;

	struct Tile {
		int GID;
		int firstGID;
		int ID;
		std::string path;
		bool isFromTileSet;
		TileProperty properties;
	};

	struct Layer {
		short int id;
		int width;
		int height;
		std::string name;
		std::vector<Tile> tiles;
		std::vector<std::pair<int, int>> coordinates;
	};
	std::vector<Layer> layers; // Pierwsze wchodzą najgłębsze warstwy

	void setTilesInfo();
	void setTilesPath();
	void setTilesAnimation();
	void setTilesHitboxes();

public:
	Map(std::string mapPath);
	~Map();
	void printInfo();
	static std::map<uint32_t, Tile> tilesInfo;


};

