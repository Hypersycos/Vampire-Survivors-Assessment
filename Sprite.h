#pragma once

class World;

#include "Image.h"
#include "Vector.h"
#include "Canvas.h"
#include "InputHandler.h"
#include <fstream>

class Sprite
{
protected:
	Vector<float> position;
	Vector<float> size;
	float scale;
	ImageSet image;

public:
	bool enabled;

	Sprite();

	Sprite(ImageSet img);

	Sprite(ImageSet img, Vector<float> position);

	void SetImage(unsigned int i);

	void SetImageSet(ImageSet set);

	void AddImage(GamesEngineeringBase::Image* img);

	ImageSet& GetImage();

	void SetScale(float s);

	Vector<float> GetSize();

	void SetPosition(Vector<float> pos);

	void SetPosition(Vector<int> pos);

	Vector<float> GetPosition();

	Vector<float> GetTopLeft();

	void SetTopLeftPosition(Vector<float> position);

	void Move(Vector<float> distance);

	void Draw(Canvas& canvas, Vector<float> offset, float zoom, Canvas::RenderMethod renderMethod, bool blankIfDisabled = false);

	virtual void Update(World* world, InputHandler& input);

	virtual void Serialize(std::ostream& stream);
	virtual void Deserialize(std::istream& stream);
};