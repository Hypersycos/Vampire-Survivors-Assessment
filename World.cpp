#include "World.h"

int World::TileAt(Vector<int> position)
{
	return this->TileAt(position.x, position.y);
}

int World::TileAt(Vector<float> position)
{
	return this->TileAt((int)round(position.x), (int)round(position.y));
}

GamesEngineeringBase::Image* World::GetTileImage(int index)
{
	return &tileImages[index];
}

int World::GetTileSize() const
{
	return tileSize;
}