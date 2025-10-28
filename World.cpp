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
DynamicArray<Enemy>& World::GetEnemies()
{
	return enemies;
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

	float* distArr = new float[N];
	for (int i = 0; i < N; i++)
	{
		arr[i] = nullptr;
		distArr[i] = maxRange + 1;
	}

	for (Enemy* enemy : enemies)
	{
		if (enemy != nullptr)
		{
			float distance = comparer(enemy);
			if (distance < distArr[N-1])
			{
				int i = N-1;
				while (i >= 0 && distArr[--i] > distance)
				{
				}
				arr[++i] = enemy;
				distArr[i] = distance;
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
	for (Enemy* e : enemies)
	{
		if (e != nullptr)
			e->Update(this, inputHandler);
	}
}