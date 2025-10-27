#pragma once

#include "Vector.h"
#include "GamesEngineeringBase.h"
#include "Sprite.h"
#include "World.h"
#include "Enums.h"
#include "Canvas.h"

class Camera
{
	Vector<unsigned int> canvasDimensions;
	Vector<unsigned int> tileDimensions;
	Vector<float> cameraPosition;
	Vector<float> cameraTopLeft;
	Vector<int> tileCentre;
	RenderMethod renderMethod;
	float zoom;
	Sprite** tiles;
	Canvas canvas;
	World* world;

	void Retile();

public:
	Camera(World* world, Canvas canvas);

	void ChangeZoom(float direction);

	void Rescale(float newZoom);

	void Move(Vector<float> movement);

	void Redraw();

	~Camera();
};