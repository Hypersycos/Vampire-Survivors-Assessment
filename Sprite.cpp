#include "Sprite.h"
#include "World.h"

Sprite::Sprite() : scale(1), enabled(false), image()
{
}

Sprite::Sprite(ImageSet img) : image(img), enabled(false), scale(1)
{
	SetScale(1);
}

Sprite::Sprite(ImageSet img, Vector<float> position) : image(img), position(position), scale(1)
{
	SetScale(1);
}

void Sprite::SetImage(unsigned int i)
{
	image.SetImage(i);
	SetScale(scale);
}

void Sprite::SetImageSet(ImageSet set)
{
	image = set;
	SetScale(scale);
}

void Sprite::AddImage(GamesEngineeringBase::Image* img)
{
	image.AddImage(img);
}

ImageSet& Sprite::GetImage()
{
	return image;
}

void Sprite::SetScale(float s)
{
	scale = s;
	size = Vector<float>((float)image.GetWidth(), (float)image.GetHeight()) * s;
}

Vector<float> Sprite::GetSize()
{
	return size;
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
	if (std::isnan(distance.x))
		distance.x = 0;
	if (std::isnan(distance.y))
		distance.y = 0;
	position += distance;
}

void Sprite::Draw(Canvas& canvas, Vector<float> offset, float zoom, Canvas::RenderMethod renderMethod, bool blankIfDisabled)
{
	if (!enabled)
	{
		if (!blankIfDisabled)
			return;
		else
			renderMethod = Canvas::Blank;
	}
	Vector<float> adjustedPosition = (GetTopLeft() - offset) * zoom;
	canvas.Draw(image, adjustedPosition, size * zoom, Vector<float>(0, 0), zoom * scale, renderMethod);
};

void Sprite::Update(World* world, InputHandler& input)
{

}

void Sprite::Serialize(std::ostream& stream)
{
	stream.write(reinterpret_cast<char*>(&position), sizeof(position));
	stream.write(reinterpret_cast<char*>(&scale), sizeof(scale));
}

void Sprite::Deserialize(std::istream& stream)
{
	stream.read(reinterpret_cast<char*>(&position), sizeof(position));
	stream.read(reinterpret_cast<char*>(&scale), sizeof(scale));
	SetScale(scale);
}
