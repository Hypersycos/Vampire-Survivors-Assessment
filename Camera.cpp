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
	int zoom;
	int tilesize;
	Sprite** tiles;
	GamesEngineeringBase::Window& canvas;
	World* world;

	void Retile()
	{
		lastRetile = intCameraPosition / tilesize;

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
					tiles[i][j].SetPosition((offset + Vector<int>(i, j)) * tilesize - Vector<int>(tilesize / 2, tilesize / 2));
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

		Rescale(1);
	}

	void ChangeZoom(int direction)
	{
		if (zoom + direction > 0)
			Rescale(direction + zoom);
	}

	void Rescale(int newZoom)
	{
		zoom = newZoom;
		tilesize = zoom * TILESIZE;

		tileDimensions = Vector<int>(canvasDimensions.x / tilesize + 2, canvasDimensions.y / tilesize + 2);

		tiles = new Sprite * [tileDimensions.x];
		for (int i = 0; i < tileDimensions.x; i++)
		{
			tiles[i] = new Sprite[tileDimensions.y];
			for (int j = 0; j < tileDimensions.y; j++)
			{
				tiles[i][j] = Sprite();
				tiles[i][j].SetScale(zoom);
			}
		}

		Retile();
	}

	void Move(Vector<float> movement)
	{
		cameraPosition += movement;
		intCameraPosition.x = round(cameraPosition.x);
		intCameraPosition.y = round(cameraPosition.y);
		if (abs(lastRetile.x - cameraPosition.x / tilesize) >= 1 || abs(lastRetile.y - cameraPosition.y / tilesize) >= 1)
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