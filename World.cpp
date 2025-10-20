#include "Vector.cpp"
#include "Tile.cpp"
#include "Player.cpp"
#include "Enemy.cpp"
#include "GamesEngineeringBase.h"

#pragma once

class World
{
protected:
	int enemyCount;
	Enemy* enemies;
	Player player;
	GamesEngineeringBase::Image* tileImages;

public:
	int TileAt(Vector<int> position)
	{
		return this->TileAt(position.x, position.y);
	}
	virtual int TileAt(int x, int y) = 0;

	GamesEngineeringBase::Image* GetImage(int index)
	{
		return &tileImages[index];
	}
};

class TestWorld : public World
{
	int** tiles;

public:
	TestWorld()
	{
		tiles = new int* [200];
		for (int i = 0; i < 200; i++)
		{
			tiles[i] = new int[200];
			for (int j = 0; j < 200; j++)
			{
				tiles[i][j] = rand() % 4;
			}
		}

		tileImages = new GamesEngineeringBase::Image[4];
		const char* paths[] = { "Resources/0.png", "Resources/1.png", "Resources/2.png", "Resources/3.png" };
		for (int i = 0; i < 4; i++)
		{
			tileImages[i].load(paths[i]);
		}
	}

	int TileAt(int x, int y) override
	{
		x += 100;
		y += 100;
		if (x < 200 && x >= 0 && y < 200 && y >= 0)
			return tiles[x][y];
		else
			return -1;
	}
};