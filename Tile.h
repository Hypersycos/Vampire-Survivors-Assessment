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

	static void LoadTiles();
	static void SaveTiles();

public:
	inline static const unsigned int tileSize{ 32 };

	static Tile* GetTile(unsigned int i);

	FixedArray<bool, 4> collisionMatrix;
	FixedArray<float, 2> speedMatrix;
	std::string imagePath;
	GamesEngineeringBase::Image image;

	Tile(FixedArray<bool, 4>& collisionMatrix, FixedArray<float, 2>& speedMatrix, std::string imagePath);
	Tile(std::initializer_list<bool> collisionMatrix, std::initializer_list<float> speedMatrix, std::string imagePath);

	void Apply(Character* character);
	void Unapply(Character* character);
};