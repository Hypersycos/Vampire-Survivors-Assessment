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
	DynamicArray<Enemy*> enemies{};
	DynamicArray<Projectile*> enemyProjectiles{};
	DynamicArray<Projectile*> playerProjectiles{};
	DynamicArray<Powerup*> powerups{};
	Player* player = nullptr;

	World();
	~World();

	void Free();

	void Load(std::istream& stream);

	void Save(std::ostream& stream);

public:

	enum WorldType : char
	{
		Fixed,
		FixedRepeating,
		Infinite
	};

	virtual WorldType GetType() = 0;

	virtual void LoadState(std::istream& stream) = 0;

	virtual void SaveState(std::ostream& stream) = 0;

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