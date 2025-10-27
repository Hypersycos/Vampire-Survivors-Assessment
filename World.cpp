#include "World.h"

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
	return GetNearestEnemy(maxRange, player.GetPosition());
}

void World::GetNearestNEnemies(float maxRange, Vector<float> position, Array<Enemy*>& arr, Comparer)
{
	int N = arr.GetSize();
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
			if (distance < distArr[4])
			{
				int i = 4;
				while (i >= 0 && distArr[--i] > distance)
				{
				}
				arr[++i] = enemy;
				distArr[i] = distance;
			}
		}
	}
}

void World::GetNearestNEnemiesToPlayer(float maxRange, Array<Enemy*>& arr, Comparer)
{
	return GetNearestNEnemies(maxRange, player.GetPosition(), arr, comparer);
}