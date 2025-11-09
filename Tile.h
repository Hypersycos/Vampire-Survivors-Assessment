#pragma once
#include "GamesEngineeringBase.h"
#include "DynamicArray.h"
#include "FixedArray.h"
#include "Character.h"
#include <string>

class Tile
{
	static DynamicArray<Tile*> tiles;
	static bool tilesLoaded;
	static std::string currentPath;
	unsigned int index;
	static inline unsigned int tileCount = 0;

public:
	inline static const unsigned int tileSize{ 32 };

	static Tile* GetTile(unsigned int i);

	static void LoadTiles(std::string path = "Resources/Tiles.dat");
	static void SaveTiles(std::string path = "Resources/Tiles.dat");
	static std::string GetCurrentPath();
	static unsigned int GetTileCount();

	FixedArray<bool, 4> collisionMatrix;
	FixedArray<float, 2> speedMatrix;
	std::string imagePath;
	GamesEngineeringBase::Image image;

	Tile(FixedArray<bool, 4>& collisionMatrix, FixedArray<float, 2>& speedMatrix, std::string imagePath);
	Tile(std::initializer_list<bool> collisionMatrix, std::initializer_list<float> speedMatrix, std::string imagePath);
	~Tile();

	void Apply(Character* character);
	void Unapply(Character* character);
	unsigned int GetIndex();
};