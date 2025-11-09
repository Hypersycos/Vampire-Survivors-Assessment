#include "InfiniteWorld.h"

#define widthLoop 4096
#define heightLoop 4096

World::WorldType InfiniteWorld::GetType()
{
	return WorldType::Infinite;
}

InfiniteWorld::InfiniteWorld() : seed(0)
{
	//caches tiles
	//not needed with current terrible generator, but would be useful with a more expensive one
	tiles = new char* [widthLoop];
	xLoops = new char* [widthLoop];
	yLoops = new char* [widthLoop];
	for (int i = 0; i < widthLoop; i++)
	{
		tiles[i] = new char[heightLoop];
		xLoops[i] = new char[heightLoop];
		yLoops[i] = new char[heightLoop];
	}
}

InfiniteWorld::InfiniteWorld(long seed) : InfiniteWorld()
{
	this->seed = seed;
	Generate();
}

inline int RealModulo(int i, int n)
{ //standard C++ modulo can return negatives
	return (i % n + n) % n;
}

Tile* InfiniteWorld::TileAt(int x, int y)
{
	char xLoop = x / widthLoop;
	char yLoop = y / heightLoop;

	int boundedX = RealModulo(x, widthLoop);
	int boundedY = RealModulo(y, heightLoop);

	if (xLoops[boundedX][boundedY] != xLoop || yLoops[boundedX][boundedY] != yLoop)
	{ //generate new tile if our cached one is from wrong area
		tiles[boundedX][boundedY] = GenerateTile(x, y);
		xLoops[boundedX][boundedY] = xLoop;
		yLoops[boundedX][boundedY] = yLoop;
	}

	return Tile::GetTile(tiles[boundedX][boundedY]);
}

void InfiniteWorld::LoadState(std::istream& worldState)
{
	worldState.read(reinterpret_cast<char*>(&seed), sizeof(seed));
	Generate();
	World::Load(worldState);
}

void InfiniteWorld::SaveState(std::ostream& worldState)
{
	worldState.write(reinterpret_cast<char*>(&seed), sizeof(seed));
	World::Save(worldState);
}

void InfiniteWorld::Generate()
{
	char currentXLoop = 0;
	char currentYLoop = 0;
	if (player != nullptr)
	{
		currentXLoop = player->GetPosition().x / widthLoop;
		currentYLoop = player->GetPosition().y / heightLoop;
	}

	for (int i = 0; i < widthLoop; i++)
	{
		for (int j = 0; j < heightLoop; j++)
		{
			tiles[i][j] = GenerateTile(i + (int)currentXLoop * widthLoop, j + (int)currentXLoop * widthLoop);
			xLoops[i][j] = currentXLoop;
			yLoops[i][j] = currentYLoop;
		}
	}
}

char InfiniteWorld::GenerateTile(int x, int y)
{
	//generator should be stateless
	int ran = RealModulo(((x * 10 + y) * (abs(seed) + 1) + seed), 64);
	if (ran < 40)
		return 0;
	else if (ran < 60)
		return 1;
	else if (ran < 62)
		return 2;
	else
		return 3;
}

InfiniteWorld::~InfiniteWorld()
{
	for (int i = 0; i < widthLoop; i++)
	{
		delete[] tiles[i];
		delete[] xLoops[i];
		delete[] yLoops[i];
	}
	delete[] tiles;
	delete[] xLoops;
	delete[] yLoops;
}
