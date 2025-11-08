#pragma once

#include "Vector.h"
#include "GamesEngineeringBase.h"
#include "Sprite.h"
#include "World.h"
#include "Canvas.h"
#include "CameraTarget.h"

class Camera
{
	Vector<unsigned int> canvasDimensions;
	Vector<unsigned int> tileDimensions;
	CameraTarget* cameraTarget;
	Vector<float> cameraTopLeft;
	Vector<int> tileCentre;
	Canvas::RenderMethod renderMethod;
	int zoomAccumulator{ 0 };
	float zoom{ 1 };
	Sprite** tiles;
	Canvas& canvas;
	World* world;

	void Retile();

public:
	Camera(World* world, Canvas& canvas);
	Camera(World* world, Canvas& canvas, CameraTarget* target);

	void SetWorld(World* world);

	void ChangeZoom(float direction);

	void Rescale(float newZoom);

	void Redraw();

	void UpdatePosition(InputHandler& inputHandler);

	Vector<float> GetCameraTopLeft();

	Vector<unsigned int> GetCameraViewSize();

	~Camera();
};