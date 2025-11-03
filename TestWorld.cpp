#include "World.h"

#pragma once

class TestWorld : public World
{
	int** tiles;
	GamesEngineeringBase::Image* playerImage;

public:
	TestWorld() : World(new std::string[4]{ "Resources/0.png", "Resources/1.png", "Resources/2.png", "Resources/3.png" }, 4)
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

		playerImage = new GamesEngineeringBase::Image;
		playerImage->load("Resources/L.png");
		player = new Player{};
		player->SetImage(playerImage);
		player->enabled = true;
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

	~TestWorld()
	{
		delete player;
	}
};