#pragma once

#include "FixedWorld.h"

class RepeatingFixedWorld : public FixedWorld
{
public:
	WorldType GetType() override;

	RepeatingFixedWorld();

	RepeatingFixedWorld(int x, int y, int seed);

	RepeatingFixedWorld(int x, int y, char fill);

	Tile* TileAt(int x, int y) override;

	void SetTile(int x, int y, char tile) override;
};