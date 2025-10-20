#include "GamesEngineeringBase.h"
#include "Vector.cpp"

class Sprite
{
	Vector<int> position;
	Vector<int> size;
	int scale;
	GamesEngineeringBase::Image* image;

public:
	bool enabled;

	Sprite() : scale(1), enabled(false), image(NULL)
	{
	}

	Sprite(GamesEngineeringBase::Image* img) : image(img), enabled(false), scale(1)
	{
		SetScale(1);
	}

	Sprite(GamesEngineeringBase::Image* img, Vector<int> position) : image(img), position(position), scale(1)
	{
		SetScale(1);
	}

	void SetImage(GamesEngineeringBase::Image* img)
	{
		image = img;
		SetScale(scale);
	}

	void SetScale(int s)
	{
		scale = s;
		if (image != NULL)
			size = Vector<int>(image->width, image->height) * s;
	}

	void SetPosition(Vector<int> pos)
	{
		position = pos;
	}

	Vector<int> GetPosition()
	{
		return position;
	}

	Vector<int> GetTopLeft()
	{
		return position - (size / 2);
	}

	void SetTopLeftPosition(Vector<int> position)
	{
		SetPosition(position + size / 2);
	}

	void Move(Vector<int> distance)
	{
		position += distance;
	}

	void Draw(GamesEngineeringBase::Window& canvas, Vector<int> offset)
	{
		if (!enabled)
			return;

		Vector<int> adjustedPosition = GetTopLeft() - offset;

		int xmax = min(size.x, (int)canvas.getWidth() - adjustedPosition.x);
		int ymax = min(size.y, (int)canvas.getHeight() - adjustedPosition.y);
		int xmin = max(0, -adjustedPosition.x);
		int ymin = max(0, -adjustedPosition.y);

		for (int i = xmin; i < xmax; i++)
		{
			int x = adjustedPosition.x + i;

			for (int j = ymin; j < ymax; j++)
			{
				int y = adjustedPosition.y + j;

				int spriteX = i / scale;
				int spriteY = j / scale;

				unsigned char alpha = image->alphaAtUnchecked(spriteX, spriteY);
				if (alpha == 0)
					continue;
				else if (alpha < 255)
				{
					//handles partial transparency by adding back buffer and sprite values together
					//weighted by (255 - alpha) and alpha respectively

					unsigned char* colour = image->atUnchecked(spriteX, spriteY);
					int bAlpha = 255 - alpha;

					unsigned char* backBuffer = canvas.getBackBuffer();
					int pixelIndex = ((y * canvas.getWidth()) + x) * 3;
					unsigned char* pixel = &backBuffer[pixelIndex];

					unsigned char alphaPixel[3];
					alphaPixel[0] = (pixel[0] * bAlpha) / 255 + (colour[0] * alpha) / 255;
					alphaPixel[1] = (pixel[1] * bAlpha) / 255 + (colour[1] * alpha) / 255;
					alphaPixel[2] = (pixel[2] * bAlpha) / 255 + (colour[2] * alpha) / 255;
					canvas.draw(x, y, alphaPixel);
				}
				else
					canvas.draw(x, y, image->atUnchecked(spriteX, spriteY));
			}
		}
	}
};