#include "Vector.h"
#include "GamesEngineeringBase.h"
#include "Sprite.h"
#include "World.h"
#include "Enums.h"
#include "Canvas.h"

#define tilesize world->GetTileSize()

class Camera
{
	Vector<unsigned int> canvasDimensions;
	Vector<unsigned int> tileDimensions;
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
					tiles[i][j].SetImage(world->GetTileImage(tileType));
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
		canvasDimensions = Vector<unsigned int>(canvas.getWidth(), canvas.getHeight());

		Rescale(1);
	}

	void ChangeZoom(float direction)
	{
		if (zoom + direction > 0)
			Rescale(direction + zoom);
	}

	void Rescale(float newZoom)
	{
		for (unsigned int i = 0; i < tileDimensions.x; i++)
		{
			delete[] tiles[i];
		}
		delete[] tiles;

		zoom = newZoom;
		unsigned int zoomedTilesize = zoom * tilesize;

		tileDimensions = Vector<unsigned int>((canvasDimensions.x + zoomedTilesize - 1) / zoomedTilesize + 1,
									 (canvasDimensions.y + zoomedTilesize - 1) / zoomedTilesize + 1);

		tiles = new Sprite * [tileDimensions.x];
		for (unsigned int i = 0; i < tileDimensions.x; i++)
		{
			tiles[i] = new Sprite[tileDimensions.y];
			for (unsigned int j = 0; j < tileDimensions.y; j++)
			{
				tiles[i][j] = Sprite();
			}
		}

		cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2.0 / zoom;
		cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2.0 / zoom;

		//TODO: Why is this needed?
		canvas.clear();

		Retile();
	}

	void Move(Vector<float> movement)
	{
		cameraPosition += movement;
		cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2.0 / zoom;
		cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2.0 / zoom;
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
		for (unsigned int i = 0; i < tileDimensions.x; i++)
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
		for (unsigned int i = 0; i < tileDimensions.x; i++)
		{
			delete[] tiles[i];
		}
		delete[] tiles;
	}
};