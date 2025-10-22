#include "Vector.cpp"
#include "GamesEngineeringBase.h"
#include "Sprite.cpp"
#include "World.cpp"
#include "helpers/array.cpp"
#include "Enums.cpp"
#include <iostream>

#define tilesize world->GetTileSize()

class Camera
{
	Vector<int> canvasDimensions;
	Vector<int> tileDimensions;
	Vector<float> cameraPosition;
	Vector<int> tileCentre;
	RenderMethod renderMethod = RenderMethod::Integer;
	int zoom;
	Sprite** tiles;
	GamesEngineeringBase::Window& canvas;
	World* world;

	void Retile()
	{
		Vector<int> cameraOffset = Vector<int>(round(cameraPosition.x / tilesize), round(cameraPosition.y / tilesize));
		tileCentre.x = cameraOffset.x * tilesize;
		tileCentre.y = cameraOffset.y * tilesize;
		for (int i = 0; i < tileDimensions.x; i++)
		{
			for (int j = 0; j < tileDimensions.y; j++)
			{
				int tileType = world->TileAt(Vector<int>(i, j) + cameraOffset);
				if (tileType != -1)
				{
					tiles[i][j].enabled = true;
					tiles[i][j].SetImage(world->GetImage(tileType));
					tiles[i][j].SetPosition((cameraOffset + Vector<int>(i, j)) * tilesize);
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
		for (int i = 0; i < tileDimensions.x; i++)
		{
			delete[] tiles[i];
		}
		delete[] tiles;

		zoom = newZoom;
		int zoomedTilesize = zoom * tilesize;

		tileDimensions = Vector<int>((canvasDimensions.x + zoomedTilesize - 1) / zoomedTilesize + 1,
									 (canvasDimensions.y + zoomedTilesize - 1) / zoomedTilesize + 1);

		tiles = new Sprite * [tileDimensions.x];
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
		if (abs(tileCentre.x - cameraPosition.x) >= tilesize / 2 || abs(tileCentre.y - cameraPosition.y) >= tilesize / 2)
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
			sprites[i].Draw(canvas, cameraPosition, zoom, renderMethod);
		}
	}

	void Draw(Sprite** sprites, unsigned int count)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			sprites[i]->Draw(canvas, cameraPosition, zoom, renderMethod);
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