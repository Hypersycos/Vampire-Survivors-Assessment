#pragma once

#include "Vector.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "GamesEngineeringBase.h"
#include "helpers/array.cpp"

#pragma once

//typedef float(*comparer)(Enemy*);

#define Comparer float(*comparer)(Enemy*)

class World
{
protected:
	unsigned int enemyCount;
	unsigned int tileSize = 32;
	Array<Enemy*> enemies;
	Player* player;
	GamesEngineeringBase::Image* tileImages;

	World() : enemies(Array<Enemy*>(50)) {}

public:
	int TileAt(Vector<int> position);

	virtual int TileAt(int x, int y) = 0;

	int TileAt(Vector<float> position);

	GamesEngineeringBase::Image* GetTileImage(int index);

	int GetTileSize() const;

	Enemy* GetNearestEnemy(float maxRange, Vector<float> position);

	Enemy* GetNearestEnemyToPlayer(float maxRange);

	void GetNearestNEnemies(float maxRange, Vector<float> position, Array<Enemy*>& arr, Comparer);

	void GetNearestNEnemiesToPlayer(float maxRange, Array<Enemy*>& arr, Comparer);
};