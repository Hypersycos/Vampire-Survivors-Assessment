#include "Vector.cpp"
#include "GamesEngineeringBase.h"
#include "Sprite.cpp"
#include "World.cpp"
#include "helpers/array.cpp"

#define TILESIZE 32

class Camera
{
	Vector<int> canvasDimensions;
	Vector<int> tileDimensions;
	Vector<float> cameraPosition;
	Vector<int> intCameraPosition;
	Vector<int> lastRetile;
	Sprite** tiles;
	GamesEngineeringBase::Window& canvas;
	World* world;

	void Retile()
	{
		lastRetile = intCameraPosition / TILESIZE;

		Vector<int> offset = lastRetile;
		for (int i = 0; i < tileDimensions.x; i++)
		{
			for (int j = 0; j < tileDimensions.y; j++)
			{
				int tileType = world->TileAt(Vector<int>(i, j) + offset);
				if (tileType != -1)
				{
					tiles[i][j].enabled = true;
					tiles[i][j].SetImage(world->GetImage(tileType));
					tiles[i][j].SetPosition((offset + Vector<int>(i, j)) * TILESIZE - Vector<int>(TILESIZE / 2, TILESIZE / 2));
				}
				else
				{
					tiles[i][j].enabled = false;
				}
			}
		}
	}

public:
	Camera(World* world, GamesEngineeringBase::Window& canvas) : world(world), canvas(canvas)
	{
		canvasDimensions = Vector<int>(canvas.getWidth(), canvas.getHeight());

		tileDimensions = Vector<int>(canvasDimensions.x / TILESIZE + 2, canvasDimensions.y / TILESIZE + 2);

		tiles = new Sprite* [tileDimensions.x];
		for (int i = 0; i < tileDimensions.x; i++)
		{
			tiles[i] = new Sprite[tileDimensions.y];
			for (int j = 0; j < tileDimensions.y; j++)
			{
				tiles[i][j] = Sprite();
			}
		}

		Retile();
	}

	void Move(Vector<float> movement)
	{
		cameraPosition += movement;
		intCameraPosition.x = round(cameraPosition.x);
		intCameraPosition.y = round(cameraPosition.y);
		if (abs(lastRetile.x - cameraPosition.x / TILESIZE) >= 1 || abs(lastRetile.y - cameraPosition.y / TILESIZE) >= 1)
		{
			Retile();
		}
	}

	void Clear()
	{
		canvas.clear();
		for (int i = 0; i < tileDimensions.x; i++)
		{
			Draw(tiles[i], tileDimensions.y);
		}
	}

	void Draw(Sprite* sprites, unsigned int count)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			sprites[i].Draw(canvas, intCameraPosition);
		}
	}

	void Draw(Sprite** sprites, unsigned int count)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			sprites[i]->Draw(canvas, intCameraPosition);
		}
	}

	~Camera()
	{
		for (int i = 0; i < tileDimensions.x; i++)
		{
			delete[] tiles[i];
		}
		delete[] tiles;
	}
};