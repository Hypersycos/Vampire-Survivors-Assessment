#include "Tile.h"
#include <fstream>
#include <filesystem>

DynamicArray<Tile*> Tile::tiles{ 4 };
bool Tile::tilesLoaded = false;

void Tile::LoadTiles()
{
	if (tiles.GetCurrentSize() != 0)
	{
		while (tiles.GetCurrentSize() > 0)
		{
			delete tiles[tiles.GetCurrentSize() - 1];
			tiles.Remove(tiles.GetCurrentSize() - 1);
		}
	}

	if (!std::filesystem::exists("Resources/tiles.dat"))
	{
		tiles.Add(new Tile({ false, false, false, false }, { 1, 1 }, "Resources/0.png"));
		tiles.Add(new Tile({ false, false, false, false }, { 1, 1.2 }, "Resources/13.png"));
		tiles.Add(new Tile({ false, false, false, false }, { 0.75, 0.75 }, "Resources/14.png"));
		tiles.Add(new Tile({ false, false, false, true }, { 1, 1 }, "Resources/24.png"));
		SaveTiles();
		tilesLoaded = true;
		return;
	}

	std::ifstream tileFile{ "Resources/tiles.dat", std::ios::binary };

	int count;
	tileFile.read(reinterpret_cast<char*>(&count), sizeof(count));

	for (int i = 0; i < count; i++)
	{
		FixedArray<bool, 4> collMatrix;
		char bools;
		tileFile.read(&bools, 1);
		for (int j = 0; j < 4; j++)
		{ //stores all 4 bools in a single byte
			collMatrix[j] = bools & (1 << 3);
			bools <<= 1;
		}

		FixedArray<float, 2> speedMatrix;
		for (int j = 0; j < 2; j++)
		{
			float f;
			tileFile.read(reinterpret_cast<char*>(&f), sizeof(f));
			speedMatrix[j] = f;
		}

		size_t length;
		tileFile.read(reinterpret_cast<char*>(&length), sizeof(length));

		char* imagePath = new char[length + 1];
		tileFile.read(imagePath, length);
		imagePath[length] = '\0';

		tiles.Add(new Tile(collMatrix, speedMatrix, imagePath));
	}
	tilesLoaded = true;
	tileFile.close();
}

void Tile::SaveTiles()
{
	std::ofstream tileFile{ "Resources/tiles.dat", std::ios::binary | std::ios::trunc };

	int size = tiles.GetCurrentSize();
	tileFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

	for (Tile* tile : tiles)
	{
		char bools = 0;
		for (bool coll : tile->collisionMatrix)
		{ //separate bools out
			bools <<= 1;
			bools |= coll;
		}
		tileFile.write(&bools, 1);

		for (float speed : tile->speedMatrix)
		{
			tileFile.write(reinterpret_cast<const char*>(&speed), sizeof(speed));
		}

		size_t pathLength = tile->imagePath.size();

		tileFile.write(reinterpret_cast<const char*>(& pathLength), sizeof(pathLength));
		tileFile.write(tile->imagePath.c_str(), pathLength);
	}
	tileFile.close();
}

Tile* Tile::GetTile(unsigned int i)
{
	if (!tilesLoaded)
		LoadTiles();
	if (i < 0 || i >= tiles.GetCurrentSize())
		return nullptr;
	return tiles[i];
}

Tile::Tile(FixedArray<bool, 4>& collisionMatrix, FixedArray<float, 2>& speedMatrix, std::string imagePath) : imagePath(imagePath), collisionMatrix(collisionMatrix), speedMatrix(speedMatrix)
{
	image.load(imagePath);
}

Tile::Tile(std::initializer_list<bool> collisionMatrix, std::initializer_list<float> speedMatrix, std::string imagePath) : imagePath(imagePath), collisionMatrix(collisionMatrix), speedMatrix(speedMatrix)
{
	image.load(imagePath);
}

void Tile::Apply(Character* character)
{
	character->SetSpeedScalar(speedMatrix[character->getLayer() - 2]);
}

void Tile::Unapply(Character* character)
{
	character->SetSpeedScalar(1);
}
