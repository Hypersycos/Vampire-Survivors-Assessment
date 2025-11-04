#pragma once

class Sprite;

#include "Vector.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "GamesEngineeringBase.h"
#include "DynamicArray.h"
#include "Array.h"
#include "Projectile.h"

typedef float(*Comparer)(Enemy*);

class World
{
protected:
	unsigned int enemyCount{ 0 };
	unsigned int tileSize{ 32 };
	DynamicArray<Enemy*> enemies{};
	DynamicArray<Projectile*> enemyProjectiles{};
	DynamicArray<Projectile*> playerProjectiles{};
	Player* player = nullptr;
	Array<GamesEngineeringBase::Image> tileImages;

	World();
	World(std::string* tiles, unsigned int count);

public:
	void LoadImages(std::string* tiles, unsigned int count, bool freeTiles = false);

	int TileAt(Vector<int> position);

	virtual int TileAt(int x, int y) = 0;

	int TileAt(Vector<float> position);

	GamesEngineeringBase::Image* GetTileImage(int index);

	int GetTileSize() const;

	Player* GetPlayer() const;

	void SetPlayer(Player* player);

	DynamicArray<Enemy*>& GetEnemies();

	DynamicArray<Projectile*>& GetPlayerProjectiles();

	DynamicArray<Projectile*>& GetEnemyProjectiles();

	Enemy* GetNearestEnemy(float maxRange, Vector<float> position);

	Enemy* GetNearestEnemyToPlayer(float maxRange);

	void GetNearestNEnemies(float maxRange, Vector<float> position, Array<Enemy*>& arr, Comparer comparer);

	void GetNearestNEnemiesToPlayer(float maxRange, Array<Enemy*>& arr, Comparer comparer);

	void Update(InputHandler& inputHandler);

	void SpawnEnemy(Enemy* enemy);

	void SpawnProjectile(Projectile* projectile);

	bool DespawnProjectile(Projectile* projectile);

	bool DespawnProjectile(unsigned int i, Projectile* projectile);

	bool DespawnEnemy(Enemy* enemy);

	bool DespawnEnemy(unsigned int i, Enemy* enemy);
};