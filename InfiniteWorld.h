#pragma once
#include "World.h"
#include <string>

class InfiniteWorld : public World
{
	char** tiles;
	char** xLoops;
	char** yLoops;
	long seed;

public:
	WorldType GetType() override;

	InfiniteWorld();

	InfiniteWorld(long seed);

	void LoadState(std::istream& stream) override;

	void SaveState(std::ostream& stream) override;

	void Generate();

	char GenerateTile(int x, int y);

	Tile* TileAt(int x, int y) override;

	~InfiniteWorld();
};