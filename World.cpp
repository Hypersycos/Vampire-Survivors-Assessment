#include "World.h"
#include "BasicEnemy.h"
#include "Artillery.h"
#include "Runner.h"
#include "EnemyProjectile.h"
#include "PlayerProjectile.h"

#define tileSize Tile::tileSize

World::World() : player(new Player())
{
}

World::~World()
{
	Free();
}

void World::Free()
{
	int i = enemies.GetCurrentSize() - 1;
	while (i >= 0)
	{
		Enemy* e = enemies[i];
		enemies.Remove(i--);
		delete e;
	}

	i = enemyProjectiles.GetCurrentSize() - 1;
	while (i >= 0)
	{
		Projectile* p = enemyProjectiles[i];
		enemyProjectiles.Remove(i--);
		delete p;
	}

	i = playerProjectiles.GetCurrentSize() - 1;
	while (i >= 0)
	{
		Projectile* p = playerProjectiles[i];
		playerProjectiles.Remove(i--);
		delete p;
	}

	i = powerups.GetCurrentSize() - 1;
	while (i >= 0)
	{
		Powerup* p = powerups[i];
		powerups.Remove(i--);
		delete p;
	}

	if (player != nullptr)
		delete player;
}

void World::Load(std::istream& stream)
{
	Player* temp = player;
	player = nullptr;
	Free();

	player = temp;
	player->Deserialize(stream);

	unsigned int count;
	stream.read(reinterpret_cast<char*>(&count), sizeof(count));
	Enemy::Enemies enemyType;
	for (int i = 0; i < count; i++)
	{
		stream.read(reinterpret_cast<char*>(&enemyType), sizeof(enemyType));
		Enemy* e;
		switch (enemyType)
		{
		case Enemy::Artillery:
			e = new Artillery();
			break;
		case Enemy::Runner:
			e = new Runner();
			break;
		case Enemy::Basic:
		default:
			e = new BasicEnemy();
			break;
		}
		e->Deserialize(stream);
		SpawnEnemy(e);
	}

	stream.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (int i = 0; i < count; i++)
	{
		Projectile* p = new EnemyProjectile(stream);
		SpawnProjectile(p);
	}

	stream.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (int i = 0; i < count; i++)
	{
		Projectile* p = new PlayerProjectile(stream);
		SpawnProjectile(p);
	}

	stream.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (int i = 0; i < count; i++)
	{
		Powerup* p = new Powerup();
		p->Deserialize(stream);
		SpawnPowerup(p);
	}
}

void World::Save(std::ostream& stream)
{
	player->Serialize(stream);

	unsigned int count = enemies.GetCurrentSize();
	stream.write(reinterpret_cast<char*>(&count), sizeof(count));
	for (Enemy* enemy : enemies)
		enemy->Serialize(stream);

	count = enemyProjectiles.GetCurrentSize();
	stream.write(reinterpret_cast<char*>(&count), sizeof(count));
	for (Projectile* p : enemyProjectiles)
		p->Serialize(stream);

	count = playerProjectiles.GetCurrentSize();
	stream.write(reinterpret_cast<char*>(&count), sizeof(count));
	for (Projectile* p : playerProjectiles)
		p->Serialize(stream);

	count = powerups.GetCurrentSize();
	stream.write(reinterpret_cast<char*>(&count), sizeof(count));
	for (Powerup* p : powerups)
		p->Serialize(stream);
}

Tile* World::TileAt(Vector<int> position)
{
	int X = (int)round(position.x / (float)tileSize);
	return this->TileAt((int)round(position.x / (float)tileSize), (int)round(position.y / (float)tileSize));
}

Tile* World::TileAtGrid(Vector<int> position)
{
	return TileAt(position.x, position.y);
}

Tile* World::TileAt(Vector<float> position)
{
	return this->TileAt((int)round(position.x / (float)tileSize), (int)round(position.y / (float)tileSize));
}

int World::GetTileSize()
{
	return tileSize;
}

Player* World::GetPlayer() const
{
	return player;
}

void World::SetPlayer(Player* player)
{
	this->player = player;
}

DynamicArray<Enemy*>& World::GetEnemies()
{
	return enemies;
}

DynamicArray<Projectile*>& World::GetPlayerProjectiles()
{
	return playerProjectiles;
}

DynamicArray<Projectile*>& World::GetEnemyProjectiles()
{
	return enemyProjectiles;
}

DynamicArray<Powerup*>& World::GetPowerups()
{
	return powerups;
}

Enemy* World::GetNearestEnemy(float maxRange, Vector<float> position)
{
	Enemy* nearest = nullptr;
	float nearestDistance = maxRange * maxRange + 1;

	for (Enemy* enemy : enemies)
	{
		if (enemy != nullptr)
		{
			float distance = (enemy->GetPosition() - position).sqrMagnitude();
			if (distance < nearestDistance)
			{
				nearest = enemy;
				nearestDistance = distance;
			}
		}
	}

	return nearest;
}

Enemy* World::GetNearestEnemyToPlayer(float maxRange)
{
	return GetNearestEnemy(maxRange, player->GetPosition());
}

void World::GetNearestNEnemies(float maxRange, Vector<float> position, Array<Enemy*>& arr, Comparer comparer)
{
	int N = arr.GetSize();
	if (N == 0)
		return;

	float* distArr = new float[N] {};
	for (int i = 0; i < N; i++)
	{
		arr[i] = nullptr;
	}

	for (Enemy* enemy : enemies)
	{
		if ((enemy->GetPosition() - position).sqrMagnitude() <= maxRange * maxRange)
		{
			float distance = comparer(enemy);
			int i = N - 1;
			while (i >= 0 && (arr[i] == nullptr || distArr[i] > distance))
			{
				if (i < N - 1)
				{
					distArr[i+1] = distArr[i];
					arr[i+1] = arr[i];
				}
					
				distArr[i] = distance;
				arr[i--] = enemy;
			}
		}
	}
}

void World::GetNearestNEnemiesToPlayer(float maxRange, Array<Enemy*>& arr, Comparer comparer)
{
	return GetNearestNEnemies(maxRange, player->GetPosition(), arr, comparer);
}

void World::Update(InputHandler& inputHandler)
{
	player->Update(this, inputHandler);

	for (int i = 0; i < playerProjectiles.GetCurrentSize(); i++)
	{
		Projectile* p = playerProjectiles[i];
		p->Update(this, inputHandler);
		if (p->enabled == false)
		{
			DespawnProjectile(i--, p);
			delete p;
		}
	}

	for (int i = 0; i < enemies.GetCurrentSize(); i++)
	{
		Enemy* e = enemies[i];
		e->Update(this, inputHandler);
		for (int j = 0; j < playerProjectiles.GetCurrentSize(); j++)
		{
			Projectile* p = playerProjectiles[j];
			if (p->checkCollision(e))
			{
				if (e->Damage(p->GetDamage()))
				{
					DespawnProjectile(j--, p);
					delete p;
					break;
				}
				DespawnProjectile(j--, p);
				delete p;
			}
		}
	}

	for (int i = 0; i < enemyProjectiles.GetCurrentSize(); i++)
	{
		Projectile* p = enemyProjectiles[i];
		p->Update(this, inputHandler);
		if (p->enabled == false)
		{
			DespawnProjectile(i--, p);
			delete p;
		}
		else if (p->checkCollision(player))
		{
			if (player->Damage(p->GetDamage()))
				break;
			DespawnProjectile(i--, p);
			delete p;
		}
	}

	for (int i = 0; i < powerups.GetCurrentSize(); i++)
	{
		Powerup* p = powerups[i];
		if (p->checkCollision(player))
		{
			player->Powerup();
			DespawnPowerup(i--, p);
			delete p;
		}
	}
}

void World::SpawnProjectile(Projectile* projectile)
{
	if (projectile->getLayer() == CollisionSprite::CollidesWithEnemies)
	{
		playerProjectiles.Add(projectile);
	}
	else
	{
		enemyProjectiles.Add(projectile);
	}
	projectile->enabled = true;
}

bool World::DespawnProjectile(Projectile* projectile)
{
	projectile->enabled = false;
	if (projectile->getLayer() == CollisionSprite::CollidesWithEnemies)
	{
		return playerProjectiles.Remove(projectile);
	}
	else
	{
		return enemyProjectiles.Remove(projectile);
	}
}

bool World::DespawnProjectile(unsigned int i, Projectile* projectile)
{
	if (projectile->getLayer() == CollisionSprite::CollidesWithEnemies)
	{
		if (playerProjectiles[i] == projectile)
		{
			projectile->enabled = false;
			return playerProjectiles.Remove(projectile);
		}
	}
	else
	{
		if (enemyProjectiles[i] == projectile)
		{
			projectile->enabled = false;
			return enemyProjectiles.Remove(projectile);
		}
	}
	return false;
}

void World::SpawnEnemy(Enemy* enemy)
{
	enemies.Add(enemy);
	enemy->enabled = true;
}

bool World::DespawnEnemy(Enemy* enemy)
{
	enemy->enabled = false;
	return enemies.Remove(enemy);
}

bool World::DespawnEnemy(unsigned int i, Enemy* enemy)
{
	if (enemies[i] == enemy)
	{
		enemy->enabled = false;
		return enemies.Remove(enemy);
	}
	else
	{
		return false;
	}
}

void World::SpawnPowerup(Powerup* Powerup)
{
	powerups.Add(Powerup);
	Powerup->enabled = true;
}

bool World::DespawnPowerup(Powerup* Powerup)
{
	Powerup->enabled = false;
	return powerups.Remove(Powerup);
}

bool World::DespawnPowerup(unsigned int i, Powerup* Powerup)
{
	if (powerups[i] == Powerup)
	{
		Powerup->enabled = false;
		return powerups.Remove(Powerup);
	}
	else
	{
		return false;
	}
}

bool CheckLine(World* world, CollisionSprite* sprite, Vector<int>& start, Vector<int> direction, int& count)
{
	for (int i = 0; i < count; i++)
	{
		Tile* tile = world->TileAtGrid(start + direction * i);

		if (tile == nullptr || tile->collisionMatrix[sprite->getLayer()])
		{
			return true;
		}
	}
	return false;
}

void World::TryMove(CollisionSprite* sprite, Vector<float> change)
{
	Vector<float> xPos = sprite->GetPosition();
	xPos.x += change.x;

	Vector<float> yPos = sprite->GetPosition();
	yPos.y += change.y;

	int intTileSize = (int)tileSize;

	Vector<float> collBox = sprite->GetCollisionSize() - Vector<float>(0.2, 0.2);

	int xCheck = round((xPos.y + collBox.y / 2) / intTileSize) - round((xPos.y - collBox.y / 2) / intTileSize) + 1;
	int yCheck = round((yPos.x + collBox.x / 2) / intTileSize) - round((yPos.x - collBox.x / 2) / intTileSize) + 1;

	//horizontal check
	if (change.x > 0)
	{
		Vector<float> topRight = xPos;

		topRight.x += collBox.x / 2;
		topRight.y -= collBox.y / 2;

		Vector<int> topRightTile = (topRight / intTileSize).Round<int>();

		if (CheckLine(this, sprite, topRightTile, Vector<int>(0, 1), xCheck))
		{
			change.x = (topRightTile.x * intTileSize - intTileSize / 2) - (topRight.x - change.x) - 0.1f;
		}
	}
	else if (change.x < 0)
	{
		Vector<float> topLeft = xPos;

		topLeft.x -= collBox.x / 2;
		topLeft.y -= collBox.y / 2;

		Vector<int> topLeftTile = (topLeft / intTileSize).Round<int>();

		if (CheckLine(this, sprite, topLeftTile, Vector<int>(0, 1), xCheck))
		{
			change.x = (topLeftTile.x * intTileSize + intTileSize / 2) - (topLeft.x - change.x) + 0.1f;
		}
	}

	//vertical check
	if (change.y < 0)
	{
		Vector<float> topLeft = yPos;

		topLeft.x -= collBox.x / 2;
		topLeft.y -= collBox.y / 2;

		Vector<int> topLeftTile = (topLeft / intTileSize).Round<int>();

		if (CheckLine(this, sprite, topLeftTile, Vector<int>(1, 0), yCheck))
		{
			change.y = (topLeftTile.y * intTileSize + intTileSize / 2) - (topLeft.y - change.y) + 0.1f;
		}
	}
	else if (change.y > 0)
	{
		Vector<float> bottomLeft = yPos;

		bottomLeft.x -= collBox.x / 2;
		bottomLeft.y += collBox.y / 2;

		Vector<int> bottomLeftTile = (bottomLeft / intTileSize).Round<int>();

		if (CheckLine(this, sprite, bottomLeftTile, Vector<int>(1, 0), yCheck))
		{
			change.y = (bottomLeftTile.y * intTileSize - intTileSize / 2) - (bottomLeft.y - change.y) - 0.1f;
		}
	}
	sprite->Move(change);
}

#undef tileSize