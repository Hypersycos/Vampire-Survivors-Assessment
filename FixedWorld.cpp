#include "FixedWorld.h"
#include <filesystem>

World::WorldType FixedWorld::GetType()
{
	return WorldType::Fixed;
}

FixedWorld::FixedWorld() : width(0), height(0), tiles(nullptr), myPath("Saves/TempWorld.dat")
{
}

FixedWorld::FixedWorld(int x, int y, int seed) : myPath("Saves/TempWorld.dat")
{
	Generate(x, y, seed);
}

FixedWorld::FixedWorld(int x, int y, char fill) : width(x), height(x), myPath("Saves/TempWorld.dat")
{
	tiles = new char* [x];
	for (int i = 0; i < x; i++)
	{
		tiles[i] = new char[y];
		for (int j = 0; j < y; j++)
		{
			tiles[i][j] = fill;
		}
	}
}

void FixedWorld::LoadMap(std::string path)
{
	if (!std::filesystem::exists(path))
	{
		Generate(1, 1, 0);
		return;
	}

	std::ifstream tileFile{ path, std::ios::binary };

	if (tiles != nullptr)
	{
		for (int i = 0; i < width; i++)
		{
			delete[] tiles[i];
		}
		delete[] tiles;
	}

	int length;
	tileFile.read(reinterpret_cast<char*>(&length), sizeof(length));
	char* tilePath = new char[length];
	tileFile.read(tilePath, length);
	Tile::LoadTiles(tilePath);

	delete[] tilePath;

	tileFile.read(reinterpret_cast<char*>(&width), sizeof(width));
	tileFile.read(reinterpret_cast<char*>(&height), sizeof(height));

	Vector<float> pos{};

	tileFile.read(reinterpret_cast<char*>(&pos.x), sizeof(pos.x));
	tileFile.read(reinterpret_cast<char*>(&pos.y), sizeof(pos.y));

	player->SetPosition(pos);

	tiles = new char* [width];

	for (int i = 0; i < width; i++)
	{
		tiles[i] = new char[height];
		tileFile.read(&tiles[i][0], height);
	}

	tileFile.close();
}

void FixedWorld::LoadState(std::istream& worldState)
{
	int length;
	worldState.read(reinterpret_cast<char*>(&length), sizeof(length));

	char* path = new char[length];
	worldState.read(path, length);

	myPath = std::string{ path };
	LoadMap(myPath);

	delete[] path;

	World::Load(worldState);
}

void FixedWorld::SaveWorld()
{
	SaveWorld(myPath);
}

void FixedWorld::SaveWorld(std::string path)
{
	myPath = path;

	std::ofstream tileFile{ path, std::ios::binary };

	int length = Tile::GetCurrentPath().length() + 1;
	tileFile.write(reinterpret_cast<char*>(&length), sizeof(length));
	tileFile.write(Tile::GetCurrentPath().c_str(), length);

	tileFile.write(reinterpret_cast<char*>(&width), sizeof(width));
	tileFile.write(reinterpret_cast<char*>(&height), sizeof(height));

	Vector<float> pos = player->GetPosition();

	tileFile.write(reinterpret_cast<char*>(&pos.x), sizeof(pos.x));
	tileFile.write(reinterpret_cast<char*>(&pos.y), sizeof(pos.y));

	for (int i = 0; i < width; i++)
	{
		tileFile.write(&tiles[i][0], height);
	}

	tileFile.close();
}

void FixedWorld::SaveState(std::ostream& worldState)
{
	int length = myPath.length() + 1;
	worldState.write(reinterpret_cast<char*>(&length), sizeof(length));
	worldState.write(myPath.c_str(), length);

	Save(worldState);

	if (!std::filesystem::exists(myPath))
		SaveWorld(myPath);
}

void FixedWorld::Generate(int x, int y, int seed)
{
	srand(seed);
	tiles = new char* [x];
	for (int i = 0; i < x; i++)
	{
		tiles[i] = new char[y];
		for (int j = 0; j < y; j++)
		{
			int ran = rand() % 64;
			if (ran < 40)
				tiles[i][j] = 0;
			else if (ran < 60)
				tiles[i][j] = 1;
			else if (ran < 62)
				tiles[i][j] = 2;
			else
				tiles[i][j] = 3;
		}
	}
	width = x;
	height = y;
}

Tile* FixedWorld::TileAt(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		return Tile::GetTile(tiles[x][y]);
	else
		return nullptr;
}

void FixedWorld::SetTile(int x, int y, char tile)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	tiles[x][y] = tile;
}

FixedWorld::~FixedWorld()
{
	for (int i = 0; i < width; i++)
	{
		delete[] tiles[i];
	}
	delete[] tiles;
}
