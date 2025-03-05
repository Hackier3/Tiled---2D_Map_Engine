#pragma once
#include <tmxlite/Map.hpp>
#include <pugixml.hpp>
#include <variant>
#include <vector>
#include <utility> 
#include <sstream> 

struct Layer;
struct Tile;

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

	// Informacja o każdym kafelku
	struct Tile {
		int GID;
		int firstGID;
		int ID;
		std::string path = "";
		bool isFromTileSet;
		AnimatedData animation;
		std::vector<Hitbox> hitbox;
	};

	// Struktura dla konkretnych kafelkow w warstwie
	struct TileInfo {
		Tile tile; 
		int x, y;
		bool flipHorizontal;
		bool flipVertical;
		bool flipDiagonal;
	};

	struct Layer {
		Map* parent;
		Layer(Map* parent) : parent(parent) {}

		struct AnimatedTile {
			int ID;
			int x;
			int y;
			int recentTile = 0;
			std::vector<std::tuple<int, int, int>> allFramesInfo; // { ID klatki, czas trwania klatki, pozostaly czas do zmiany klatki }
		};

		short int id;
		int width;
		int height;
		std::string name;
		std::vector<TileInfo> tiles; // Kafelki na warstwie z informacjami o flipach
		sf::RenderTexture canvasTexture;
		sf::Sprite sprite; // Sprite dla warstwy
		std::vector<AnimatedTile> animatedTiles;

		void createLayerSprite();
		void setAnimatedTiles();
	};

	std::vector<std::unique_ptr<Layer>> layers;
	static std::map<uint32_t, Tile> tilesInfo;

	void setTilesInfo();
	void setTilesPath();
	void setTilesAnimation();
	void setTilesHitboxes();
	void processTileLayers();
	void drawUnderground(sf::RenderWindow& window);
	void drawUpground(sf::RenderWindow& window);

public:
	friend class World;
	friend class Animation;

	Map(std::string mapPath);
	Map(Map&&) = default;
	Map& operator=(Map&&) = default;
	~Map();
	void printInfo() const;
};