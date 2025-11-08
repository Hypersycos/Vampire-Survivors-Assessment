#include "Camera.h"
#include "FreeCamera.h"

#define tilesize world->GetTileSize()

void Camera::Retile()
{
	if (world == nullptr)
		return;

	Vector<int> cameraOffset = Vector<int>((int)round(cameraTopLeft.x / tilesize),
											(int)round(cameraTopLeft.y / tilesize));
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
			}
			else
			{
				tileType = Tile::GetTile(0);
				tiles[i][j].enabled = false;
			}
			tiles[i][j].SetImage(&tileType->image);
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

	Vector<float> cameraPosition = cameraTarget->GetPosition();

	cameraTopLeft.x = cameraPosition.x - canvas.getWidth() / 2.0f / zoom;
	cameraTopLeft.y = cameraPosition.y - canvas.getHeight() / 2.0f / zoom;

	Retile();
}

void Camera::UpdatePosition(InputHandler& inputHandler)
{
	if (inputHandler.MouseWheel() != 0)
	{
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
	{
		Retile();
	}
#pragma warning( pop )
}

Vector<float> Camera::GetCameraTopLeft()
{
	if (zoom == 1)
		return cameraTopLeft;
	else
		return cameraTarget->GetPosition() - Vector<float>(canvas.getWidth() / 2, canvas.getHeight() / 2);
}

Vector<unsigned int> Camera::GetCameraViewSize()
{
	return canvasDimensions;
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

	for (Powerup* p : world->GetPowerups())
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