#pragma once
#include "World.h"
#include <string>

class FixedWorld : public World
{
protected:
	char** tiles;
	int width;
	int height;
	std::string myPath;

public:
	WorldType GetType() override;

	FixedWorld();

	FixedWorld(int x, int y, int seed);

	FixedWorld(int x, int y, char fill);

	void LoadMap(std::string path);

	void LoadState(std::istream& stream) override;

	void SaveWorld(std::string path);

	void SaveState(std::ostream& stream) override;

	void Generate(int x, int y, int seed);

	Tile* TileAt(int x, int y) override;

	virtual void SetTile(int x, int y, char tile);

	~FixedWorld();
};