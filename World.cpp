#include "Vector.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "GamesEngineeringBase.h"

class World
{
protected:
	unsigned int enemyCount;
	unsigned int tileSize = 32;
	Enemy* enemies;
	Player player;
	GamesEngineeringBase::Image* tileImages;

public:
	int TileAt(Vector<int> position)
	{
		return this->TileAt(position.x, position.y);
	}
	virtual int TileAt(int x, int y) = 0;

	int TileAt(Vector<float> position)
	{
		return this->TileAt(position.x, position.y);
	}

	GamesEngineeringBase::Image* GetTileImage(int index)
	{
		return &tileImages[index];
	}

	int GetTileSize()
	{
		return tileSize;
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