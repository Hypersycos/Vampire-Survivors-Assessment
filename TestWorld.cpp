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
				tiles[i][j] = rand() % 5 - 1;
			}
		}

		playerImage = new GamesEngineeringBase::Image;
		playerImage->load("Resources/14.png");
		player = new Player{};
		player->SetImage(playerImage);
		player->enabled = true;
		player->SetScale(1);
	}

	int TileAt(int x, int y) override
	{
		x += 100;
		y += 100;
		if (x < 125 && x >= 75 && y < 125 && y >= 75)
			return tiles[x][y];
		else
			return -1;
	}

	~TestWorld()
	{
		delete player;
	}
};