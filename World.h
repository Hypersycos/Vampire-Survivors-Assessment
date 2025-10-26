#pragma once

#include "Vector.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "GamesEngineeringBase.h"

#pragma once

class World
{
protected:
	unsigned int enemyCount;
	unsigned int tileSize = 32;
	Enemy* enemies;
	Player* player;
	GamesEngineeringBase::Image* tileImages;

public:
	int TileAt(Vector<int> position);

	virtual int TileAt(int x, int y) = 0;

	int TileAt(Vector<float> position);

	GamesEngineeringBase::Image* GetTileImage(int index);

	int GetTileSize() const;
};