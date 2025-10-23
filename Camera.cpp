#include "Vector.cpp"
#include "GamesEngineeringBase.h"
#include "Sprite.cpp"
#include "World.cpp"
#include "helpers/array.cpp"
#include "Enums.cpp"
#include <iostream>
#include "Canvas.cpp"

#define tilesize world->GetTileSize()

class Camera
{
	Vector<int> canvasDimensions;
	Vector<int> tileDimensions;
	Vector<float> cameraPosition;
	Vector<float> cameraTopLeft;
	Vector<int> tileCentre;
	RenderMethod renderMethod = RenderMethod::Integer;
	float zoom;
	Sprite** tiles;
	Canvas canvas;
	World* world;

	void Retile()
	{
		Vector<int> cameraOffset = Vector<int>(round(cameraTopLeft.x / tilesize),
											   round(cameraTopLeft.y / tilesize));
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
					tiles[i][j].SetPosition((cameraOffset + Vector<int>(i, j)) * tilesize);
				}
			}
		}
	}

public:
	Camera(World* world, Canvas canvas) : world(world), canvas(canvas)
	{
		canvasDimensions = Vector<int>(canvas.getWidth(), canvas.getHeight());

		Rescale(1);
	}

	void ChangeZoom(float direction)
	{
		if (zoom + direction > 0)
			Rescale(direction + zoom);
	}

	void Rescale(float newZoom)
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

		cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2 / zoom;
		cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2 / zoom;

		//TODO: Why is this needed?
		canvas.clear();

		Retile();
	}

	void Move(Vector<float> movement)
	{
		cameraPosition += movement;
		cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2 / zoom;
		cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2 / zoom;
		if (abs(tileCentre.x - cameraPosition.x) >= tilesize / 2 || abs(tileCentre.y - cameraPosition.y) >= tilesize / 2)
		{
			Retile();
		}
	}

	void Clear()
	{
#ifdef enableDrawBeyondBounds
		canvas.clear();
#endif
		//canvas.clear();
		for (int i = 0; i < tileDimensions.x; i++)
		{
			Draw(tiles[i], tileDimensions.y, true);
		}
#ifdef enableDrawBeyondBounds
		canvas.DrawBoxUnsafe(Vector<unsigned int>(0, 0), canvas.GetSize(), 0, 0, 255);
#endif
	}

	void Draw(Sprite* sprite)
	{
		sprite->Draw(canvas, cameraTopLeft, zoom, renderMethod);
	}

	void Draw(Sprite* sprites, unsigned int count, bool drawDisabledAsBlank = false)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			sprites[i].Draw(canvas, cameraTopLeft, zoom, renderMethod, drawDisabledAsBlank);
		}
	}

	void Draw(Sprite** sprites, unsigned int count, bool drawDisabledAsBlank = false)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			sprites[i]->Draw(canvas, cameraTopLeft, zoom, renderMethod, drawDisabledAsBlank);
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