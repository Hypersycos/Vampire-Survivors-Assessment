#pragma once
#include "World.h"
#include <string>
#include "Vector.h"

class InfiniteWorld : public World
{
	char** tiles;
	char** xLoops;
	char** yLoops;
	Vector<double> seed;

public:
	WorldType GetType() override;

	InfiniteWorld();

	InfiniteWorld(Vector<double> seed);

	void LoadState(std::istream& stream) override;

	void SaveState(std::ostream& stream) override;

	void Generate();

	char GenerateTile(int x, int y);

	Tile* TileAt(int x, int y) override;

	~InfiniteWorld();
};