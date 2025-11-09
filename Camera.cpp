#include "Camera.h"
#include "FreeCamera.h"

#define tilesize world->GetTileSize()

void Camera::Retile()
{
	if (world == nullptr)
		return;

	//top left visible tile
	Vector<int> cameraOffset = Vector<int>((int)round(cameraTopLeft.x / tilesize),
											(int)round(cameraTopLeft.y / tilesize));

	//sets new central tile, so we know when to retile again
	tileCentre.x = cameraOffset.x * tilesize;
	tileCentre.y = cameraOffset.y * tilesize;

	for (unsigned int i = 0; i < tileDimensions.x; i++)
	{
		for (unsigned int j = 0; j < tileDimensions.y; j++)
		{
			Tile* tileType = world->TileAtGrid(Vector<int>(i, j) + cameraOffset);
			if (tileType != nullptr)
			{
				tiles[i][j].enabled = true;
				tiles[i][j].SetImage(tileType->GetIndex());
			}
			else
			{
				tiles[i][j].enabled = false;
			}
			tiles[i][j].SetPosition((cameraOffset + Vector<int>(i, j)) * tilesize);
		}
	}
}

Camera::Camera(World* world, Canvas& canvas) : world(world), canvas(canvas)
{
	canvasDimensions = Vector<unsigned int>(canvas.getWidth(), canvas.getHeight());
	cameraTarget = new FreeCamera();

	Rescale(1);
}

Camera::Camera(World* world, Canvas& canvas, CameraTarget* target) : cameraTarget(target), world(world), canvas(canvas)
{
	canvasDimensions = Vector<unsigned int>(canvas.getWidth(), canvas.getHeight());

	Rescale(1);
}

void Camera::SetWorld(World* world)
{
	this->world = world;
	Rescale(zoom);
}

void Camera::ChangeZoom(float direction)
{
	if (zoom + direction > 0)
		Rescale(direction + zoom);
}

void Camera::Rescale(float newZoom)
{
	if (world == nullptr)
		return;

	for (unsigned int i = 0; i < tileDimensions.x; i++)
	{
		delete[] tiles[i];
	}
	delete[] tiles;

	zoom = newZoom;
	unsigned int zoomedTilesize = (unsigned int)(zoom * tilesize);

	//number of tiles required to cover entire screen
	//+1 deals with extra tile required for camera positions which aren't multiples of tileSize
	//(x + (y - 1)) / y is a ceil without needing floats
	tileDimensions = Vector<unsigned int>((canvasDimensions.x + zoomedTilesize - 1) / zoomedTilesize + 1,
									(canvasDimensions.y + zoomedTilesize - 1) / zoomedTilesize + 1);

	ImageSet tileImages = {};
	for (unsigned int i = 0; i < Tile::GetTileCount(); i++)
		tileImages.AddImage(&Tile::GetTile(i)->image);

	tiles = new Sprite * [tileDimensions.x];
	for (unsigned int i = 0; i < tileDimensions.x; i++)
	{
		tiles[i] = new Sprite[tileDimensions.y];
		for (unsigned int j = 0; j < tileDimensions.y; j++)
		{
			tiles[i][j].SetImageSet(tileImages);
		}
	}

	Vector<float> cameraPosition = cameraTarget->GetPosition();

	cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2.0f / zoom;
	cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2.0f / zoom;

	Retile();
}

void Camera::UpdatePosition(InputHandler& inputHandler)
{
	if (inputHandler.MouseWheel() != 0)
	{ //allows handling of both smooth and discrete scroll wheels
		if (inputHandler.MouseWheel() > 0 && zoomAccumulator < 0 ||
			inputHandler.MouseWheel() < 0 && zoomAccumulator > 0)
			zoomAccumulator = 0;

		zoomAccumulator += inputHandler.MouseWheel();
		if (abs(zoomAccumulator) > 100)
		{
			ChangeZoom(0.25 * (zoomAccumulator / 100));
			zoomAccumulator -= (zoomAccumulator / 100) * 100;
		}
	}

	cameraTarget->Update(inputHandler);
	Vector<float> cameraPosition = cameraTarget->GetPosition();

	cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2.0f / zoom;
	cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2.0f / zoom;
	if (renderMethod == Canvas::Integer)
	{
#pragma warning( push )
#pragma warning( disable: 4244 )
		cameraTopLeft.x = round(cameraTopLeft.x);
		cameraTopLeft.y = round(cameraTopLeft.y);
	}
	if (abs(tileCentre.x - cameraPosition.x) >= tilesize / 2 || abs(tileCentre.y - cameraPosition.y) >= tilesize / 2)
	{ //if our camera is over half a tile away, then we need to shift our tiles
		Retile();
	}
#pragma warning( pop )
}

Vector<float> Camera::GetCameraTopLeftWithoutZoom()
{
	if (zoom == 1)
		return cameraTopLeft;
	else
		return cameraTarget->GetPosition() - Vector<float>(canvas.getWidth() / 2, canvas.getHeight() / 2);
}

Vector<unsigned int> Camera::GetCameraViewSizeWithoutZoom()
{
	return canvasDimensions;
}

void Camera::Redraw()
{
#ifdef enableDrawBeyondBounds
	canvas.clear();
#endif
	for (unsigned int i = 0; i < tileDimensions.x; i++)
	{
		for (unsigned int j = 0; j < tileDimensions.y; j++)
		{ //draws all tiles, blanking out invalid ones
			tiles[i][j].Draw(canvas, cameraTopLeft, zoom, renderMethod, true);
		}
	}

	for (Powerup* p : world->GetPowerups())
	{
		p->Draw(canvas, cameraTopLeft, zoom, renderMethod);
	}

	for (Enemy* e : world->GetEnemies())
	{
		e->Draw(canvas, cameraTopLeft, zoom, renderMethod);
	}

	for (Projectile* p : world->GetPlayerProjectiles())
	{
		p->Draw(canvas, cameraTopLeft, zoom, renderMethod);
	}

	for (Projectile* p : world->GetEnemyProjectiles())
	{
		p->Draw(canvas, cameraTopLeft, zoom, renderMethod);
	}

	if (world->GetPlayer() != nullptr)
		world->GetPlayer()->Draw(canvas, cameraTopLeft, zoom, renderMethod);

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