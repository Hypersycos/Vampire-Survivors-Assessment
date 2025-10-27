#include "Sprite.h"

class Sprite
{
}

Sprite::Sprite(GamesEngineeringBase::Image* img) : image(img), enabled(false), scale(1)
{
	SetScale(1);
}

Sprite::Sprite(GamesEngineeringBase::Image* img, Vector<float> position) : image(img), position(position), scale(1)
{
	SetScale(1);
}

void Sprite::SetImage(GamesEngineeringBase::Image* img)
{
	image = img;
	SetScale(scale);
}

void Sprite::SetScale(float s)
{
	scale = s;
	if (image != NULL)
		size = Vector<float>((float)image->width, (float)image->height) * s;
}

void Sprite::SetPosition(Vector<float> pos)
{
	position = pos;
}

void Sprite::SetPosition(Vector<int> pos)
{
	position = Vector<float>((float)pos.x, (float)pos.y);
}

Vector<float> Sprite::GetPosition()
{
	return position;
}

Vector<float> Sprite::GetTopLeft()
{
	return position - (size / 2);
}

void Sprite::SetTopLeftPosition(Vector<float> position)
{
	SetPosition(position + size / 2);
}

void Sprite::Move(Vector<float> distance)
{
	position += distance;
}

void Sprite::Draw(Canvas& canvas, Vector<float> offset, float zoom, RenderMethod renderMethod, bool blankIfDisabled)
{
	if (!enabled)
	{
		if (!blankIfDisabled)
			return;
		}

		switch (renderMethod)
		{
		case Integer:
			DrawInteger(canvas, offset, zoom);
			break;
		case Bilinear:
			//DrawBilinear(canvas, offset, zoom);
			break;
		case Blank:
			DrawBlank(canvas, offset, zoom);
			break;
		default:
			break;
		}
	}
};

virtual void Sprite::Update(float dt, World* world, InputHandler& input)
{

}