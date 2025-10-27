#pragma once

class Sprite;

#include "Vector.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "GamesEngineeringBase.h"
#include "helpers/array.cpp"

typedef float(*Comparer)(Enemy*);

//#define Comparer float(*comparer)(Enemy*)

class World
{
protected:
	unsigned int enemyCount{ 0 };
	unsigned int tileSize{ 32 };
	Array<Enemy*> enemies{0};
	Player* player = new Player();
	GamesEngineeringBase::Image* tileImages;

	World();

public:
	int TileAt(Vector<int> position);

	virtual int TileAt(int x, int y) = 0;

	int TileAt(Vector<float> position);

	GamesEngineeringBase::Image* GetTileImage(int index);

	int GetTileSize() const;

	Player* GetPlayer() const;

	Array<Enemy*> GetEnemies() const;

	Enemy* GetNearestEnemy(float maxRange, Vector<float> position);

	Enemy* GetNearestEnemyToPlayer(float maxRange);

	void GetNearestNEnemies(float maxRange, Vector<float> position, Array<Enemy*>& arr, Comparer comparer);

	void GetNearestNEnemiesToPlayer(float maxRange, Array<Enemy*>& arr, Comparer comparer);

	void Update(InputHandler& inputHandler);
};