#include "RepeatingFixedWorld.h"

World::WorldType RepeatingFixedWorld::GetType()
{
	return WorldType::FixedRepeating;
}

RepeatingFixedWorld::RepeatingFixedWorld() : FixedWorld()
{

}

RepeatingFixedWorld::RepeatingFixedWorld(int x, int y, int seed) : FixedWorld(x, y, seed)
{

}

RepeatingFixedWorld::RepeatingFixedWorld(int x, int y, char fill) : FixedWorld(x, y, fill)
{

}

inline int RealModulo(int number, int divisor)
{
	return (number % divisor + divisor) % divisor;
}

Tile* RepeatingFixedWorld::TileAt(int x, int y)
{ //allows same terrain to loop
	return FixedWorld::TileAt(RealModulo(x, width), RealModulo(y, height));
}

void RepeatingFixedWorld::SetTile(int x, int y, char tile)
{
	x = RealModulo(x, width);
	y = RealModulo(y, height);
	tiles[x][y] = tile;
}