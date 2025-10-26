#include "Camera.h"

#define tilesize world->GetTileSize()

void Camera::Retile()
{
	Vector<int> cameraOffset = Vector<int>((int)round(cameraTopLeft.x / tilesize),
											(int)round(cameraTopLeft.y / tilesize));
	tileCentre.x = cameraOffset.x * tilesize;
	tileCentre.y = cameraOffset.y * tilesize;
	for (unsigned int i = 0; i < tileDimensions.x; i++)
	{
		for (unsigned int j = 0; j < tileDimensions.y; j++)
		{
			int tileType = world->TileAt(Vector<int>(i, j) + cameraOffset);
			if (tileType != -1)
			{
				tiles[i][j].enabled = true;
			}
			else
			{
				tileType = 0;
				tiles[i][j].enabled = false;
			}
			tiles[i][j].SetImage(world->GetTileImage(tileType));
			tiles[i][j].SetPosition((cameraOffset + Vector<int>(i, j)) * tilesize);
		}
	}
}

Camera::Camera(World* world, Canvas canvas) : world(world), canvas(canvas)
{
	canvasDimensions = Vector<unsigned int>(canvas.getWidth(), canvas.getHeight());
	cameraPosition.x = 0;
	cameraPosition.y = 0;

	Rescale(1);
}

void Camera::ChangeZoom(float direction)
{
	if (zoom + direction > 0)
		Rescale(direction + zoom);
}

void Camera::Rescale(float newZoom)
{
	for (unsigned int i = 0; i < tileDimensions.x; i++)
	{
		delete[] tiles[i];
	}
	delete[] tiles;

	zoom = newZoom;
	unsigned int zoomedTilesize = (unsigned int)(zoom * tilesize);

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

	cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2.0f / zoom;
	cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2.0f / zoom;

	Retile();
}

void Camera::Move(Vector<float> movement)
{
	cameraPosition += movement;
	cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2.0f / zoom;
	cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2.0f / zoom;
	if (renderMethod == Integer)
	{
		cameraTopLeft.x = round(cameraTopLeft.x);
		cameraTopLeft.y = round(cameraTopLeft.y);
	}
	if (abs(tileCentre.x - cameraPosition.x) >= tilesize / 2 || abs(tileCentre.y - cameraPosition.y) >= tilesize / 2)
	{
		Retile();
	}
}

void Camera::Redraw()
{
#ifdef enableDrawBeyondBounds
	canvas.clear();
#endif
	//canvas.clear();
	for (unsigned int i = 0; i < tileDimensions.x; i++)
	{
		for (unsigned int j = 0; j < tileDimensions.y; j++)
		{
			tiles[i][j].Draw(canvas, cameraTopLeft, zoom, renderMethod, true);
		}
	}
#ifdef enableDrawBeyondBounds
	canvas.DrawBoxUnsafe(Vector<unsigned int>(0, 0), canvas.GetSize(), 0, 0, 255);
#endif
}

Camera::~Camera()
{
	for (unsigned int i = 0; i < tileDimensions.x; i++)
	{
		delete[] tiles[i];
	}
	delete[] tiles;
}