#pragma once

#include "GamesEngineeringBase.h"
#include "Vector.cpp"
#include "Enums.cpp"
#include "Canvas.cpp"

class Sprite
{
	Vector<float> position;
	Vector<float> size;
	float scale;
	GamesEngineeringBase::Image* image;

public:
	bool enabled;

	Sprite();

	Sprite(GamesEngineeringBase::Image* img);

	Sprite(GamesEngineeringBase::Image* img, Vector<float> position);

	void SetImage(GamesEngineeringBase::Image* img);

	void SetScale(float s);

	void SetPosition(Vector<float> pos);

	void SetPosition(Vector<int> pos);

	Vector<float> GetPosition();

	Vector<float> GetTopLeft();

	void SetTopLeftPosition(Vector<float> position);

	void Move(Vector<float> distance);

	void Draw(Canvas canvas, Vector<float> offset, float zoom, RenderMethod renderMethod, bool blankIfDisabled = false);
};