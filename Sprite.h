#pragma once

#include "GamesEngineeringBase.h"
#include "Vector.h"
#include "Enums.h"
#include "Canvas.h"

class Sprite
{
protected:
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

	void Draw(Canvas& canvas, Vector<float> offset, float zoom, RenderMethod renderMethod, bool blankIfDisabled = false);
};