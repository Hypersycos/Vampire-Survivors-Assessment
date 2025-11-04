#include "World.h"

World::World() : World(nullptr, 0)
{

}

World::World(std::string* tiles, unsigned int count) : enemyCount(0), tileImages(Array<GamesEngineeringBase::Image>(count))
{
	if (tiles != nullptr)
		LoadImages(tiles, count, true);
}

void World::LoadImages(std::string* tiles, unsigned int count, bool freeTiles)
{
	for (unsigned int i = 0; i < count; i++)
	{
		tileImages[i].load(tiles[i]);
	}
	if (freeTiles)
		delete[] tiles;
}

int World::TileAt(Vector<int> position)
{
	return this->TileAt(position.x, position.y);
}

int World::TileAt(Vector<float> position)
{
	return this->TileAt((int)round(position.x), (int)round(position.y));
}

GamesEngineeringBase::Image* World::GetTileImage(int index)
{
	return &tileImages[index];
}

int World::GetTileSize() const
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

	for (Projectile* p : playerProjectiles)
	{
		p->Update(this, inputHandler);
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
					DespawnEnemy(i--, e);
					delete e;
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
		if (p->checkCollision(player))
		{
			if (player->Damage(p->GetDamage()))
				break;
			DespawnProjectile(i--, p);
			delete p;
		}
	}
}

void World::SpawnEnemy(Enemy* enemy)
{
	enemies.Add(enemy);
	enemy->enabled = true;
}

void World::SpawnProjectile(Projectile* projectile)
{
	if (projectile->getLayer() == CollidesWithEnemies)
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
	if (projectile->getLayer() == CollidesWithEnemies)
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
	if (projectile->getLayer() == CollidesWithEnemies)
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