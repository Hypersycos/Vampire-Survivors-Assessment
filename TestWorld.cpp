#include "World.cpp"

#pragma once

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
	}

	int TileAt(float x, float y) override
	{
		x /= tileSize;
		y /= tileSize;

		x += 100;
		y += 100;
		if (x < 200 && x >= 0 && y < 200 && y >= 0)
			return tiles[(int)round(x)][(int)round(y)];
		else
			return -1;
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