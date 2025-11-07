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
#include "Powerup.h"

typedef float(*Comparer)(Enemy*);

class World
{
protected:
	unsigned int enemyCount{ 0 };
	DynamicArray<Enemy*> enemies{};
	DynamicArray<Projectile*> enemyProjectiles{};
	DynamicArray<Projectile*> playerProjectiles{};
	DynamicArray<Powerup*> powerups{};
	Player* player = nullptr;

	World();

public:

	Tile* TileAt(Vector<int> position);

	Tile* TileAtGrid(Vector<int> position);

	virtual Tile* TileAt(int x, int y) = 0;

	Tile* TileAt(Vector<float> position);

	static int GetTileSize();

	Player* GetPlayer() const;

	void SetPlayer(Player* player);

	DynamicArray<Enemy*>& GetEnemies();

	DynamicArray<Projectile*>& GetPlayerProjectiles();

	DynamicArray<Projectile*>& GetEnemyProjectiles();

	DynamicArray<Powerup*>& GetPowerups();

	Enemy* GetNearestEnemy(float maxRange, Vector<float> position);

	Enemy* GetNearestEnemyToPlayer(float maxRange);

	void GetNearestNEnemies(float maxRange, Vector<float> position, Array<Enemy*>& arr, Comparer comparer);

	void GetNearestNEnemiesToPlayer(float maxRange, Array<Enemy*>& arr, Comparer comparer);

	void Update(InputHandler& inputHandler);

	void SpawnProjectile(Projectile* projectile);

	bool DespawnProjectile(Projectile* projectile);

	bool DespawnProjectile(unsigned int i, Projectile* projectile);

	void SpawnEnemy(Enemy* enemy);

	bool DespawnEnemy(Enemy* enemy);

	bool DespawnEnemy(unsigned int i, Enemy* enemy);

	void SpawnPowerup(Powerup* powerup);

	bool DespawnPowerup(Powerup* enemy);

	bool DespawnPowerup(unsigned int i, Powerup* enemy);

	void TryMove(CollisionSprite* sprite, Vector<float> change);
};