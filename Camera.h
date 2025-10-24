#pragma once

#include "Vector.h"
#include "GamesEngineeringBase.h"
#include "Sprite.h"
#include "World.h"
#include "Enums.h"
#include "Canvas.h"

class Camera
{
	Vector<int> canvasDimensions;
	Vector<int> tileDimensions;
	Vector<float> cameraPosition;
	Vector<float> cameraTopLeft;
	Vector<int> tileCentre;
	RenderMethod renderMethod;
	float zoom;
	Sprite** tiles;
	Canvas canvas;
	World* world;

public:
	Camera(World* world, Canvas canvas);

	void ChangeZoom(float direction);

	void Rescale(float newZoom);

	void Move(Vector<float> movement);

	void Clear();

	void Draw(Sprite* sprite);

	void Draw(Sprite* sprites, unsigned int count, bool drawDisabledAsBlank = false);

	void Draw(Sprite** sprites, unsigned int count, bool drawDisabledAsBlank = false);

	~Camera();
};