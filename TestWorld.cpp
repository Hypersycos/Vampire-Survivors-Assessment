#include "World.h"

#pragma once

class TestWorld : public World
{
	int** tiles;
	GamesEngineeringBase::Image* playerImage;

public:
	TestWorld() : World()
	{
		tiles = new int* [200];
		for (int i = 0; i < 200; i++)
		{
			tiles[i] = new int[200];
			for (int j = 0; j < 200; j++)
			{
				int ran = rand() % 32;
				if (ran < 18)
					tiles[i][j] = 0;
				else if (ran < 28)
					tiles[i][j] = 1;
				else if (ran < 31)
					tiles[i][j] = 2;
				else
					tiles[i][j] = 3;
				//tiles[i][j] = rand() % 1;
			}
		}

		playerImage = new GamesEngineeringBase::Image;
		playerImage->load("Resources/L.png");
		player = new Player{};
		player->SetImage(playerImage);
		player->enabled = true;
		player->SetScale(0.5);
	}

	Tile* TileAt(int x, int y) override
	{
		x += 100;
		y += 100;
		if (x < 125 && x >= 75 && y < 125 && y >= 75)
			return Tile::GetTile(tiles[x][y]);
		else
			return nullptr;
	}

	~TestWorld()
	{
		delete player;
	}
};