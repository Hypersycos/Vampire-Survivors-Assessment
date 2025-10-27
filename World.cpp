#include "Vector.cpp"
#include "Tile.cpp"
#include "Player.cpp"
#include "Enemy.cpp"
#include "GamesEngineeringBase.h"
#include "helpers/array.cpp"
#include <string>

#pragma once

//typedef float(*comparer)(Enemy*);

#define Comparer float(*comparer)(Enemy*)

class World
{
protected:
	int enemyCount = 0;
	int tileSize = 32;
	Array<Enemy* > enemies;
	Player player;
	GamesEngineeringBase::Image* tileImages;

public:
	World(Array<std::string> tilePaths) : enemies(Array<Enemy *>(50))
	{
		tileImages = new GamesEngineeringBase::Image[tilePaths.GetSize()];
		for (int i = 0; i < tilePaths.GetSize(); i++)
		{
			tileImages[i].load(tilePaths[i]);
		}
	}

	int TileAt(Vector<int> position)
	{
		return this->TileAt(position.x, position.y);
	}
	virtual int TileAt(int x, int y) = 0;

	int TileAt(Vector<float> position)
	{
		return this->TileAt(position.x, position.y);
	}
	virtual int TileAt(float x, float y) = 0;

	GamesEngineeringBase::Image* GetImage(int index)
	{
		return &tileImages[index];
	}

	int GetTileSize()
	{
		return tileSize;
	}

	Player& GetPlayer()
	{
		return player;
	}

	Enemy* GetNearestEnemy(float maxRange, Vector<float> position)
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

	Enemy* GetNearestEnemyToPlayer(float maxRange)
	{
		return GetNearestEnemy(maxRange, player.GetPosition());
	}

	void GetNearestNEnemies(float maxRange, Vector<float> position, Array<Enemy *>& arr, Comparer)
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

	void GetNearestNEnemiesToPlayer(float maxRange, Array<Enemy *>& arr, Comparer)
	{
		return GetNearestNEnemies(maxRange, player.GetPosition(), arr, comparer);
	}
};