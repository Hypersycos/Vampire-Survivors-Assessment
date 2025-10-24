#include "GamesEngineeringBase.h"
#include "Vector.h"
#include "Enums.h"
#include "Canvas.h"

class Sprite
{
	Vector<float> position;
	Vector<float> size;
	float scale;
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

	Sprite(GamesEngineeringBase::Image* img, Vector<float> position) : image(img), position(position), scale(1)
	{
		SetScale(1);
	}

	void SetImage(GamesEngineeringBase::Image* img)
	{
		image = img;
		SetScale(scale);
	}

	void SetScale(float s)
	{
		scale = s;
		if (image != NULL)
			size = Vector<float>(image->width, image->height) * s;
	}

	void SetPosition(Vector<float> pos)
	{
		position = pos;
	}

	void SetPosition(Vector<int> pos)
	{
		position = Vector<float>(pos.x, pos.y);
	}

	Vector<float> GetPosition()
	{
		return position;
	}

	Vector<float> GetTopLeft()
	{
		return position - (size / 2);
	}

	void SetTopLeftPosition(Vector<float> position)
	{
		SetPosition(position + size / 2);
	}

	void Move(Vector<float> distance)
	{
		position += distance;
	}

	void DrawInteger(Canvas canvas, Vector<float> offset, float zoom)
	{
		Vector<float> adjustedPosition = (GetTopLeft() - offset) * zoom;

#ifdef enableDrawBeyondBounds
		int xmax = round(size.x * zoom);
		int ymax = round(size.y * zoom);
		int xmin = 0;
		int ymin = 0;
#else
		int xmax = round(min(size.x * zoom, (int)canvas.getWidth() - floor(adjustedPosition.x)));
		int ymax = round(min(size.y * zoom, (int)canvas.getHeight() - floor(adjustedPosition.y)));
		int xmin = round(max(0, -adjustedPosition.x));
		int ymin = round(max(0, -adjustedPosition.y));
#endif // enableDrawBeyondBounds

		for (int i = xmin; i < xmax; i++)
		{
			int x = adjustedPosition.x + i;

			for (int j = ymin; j < ymax; j++)
			{
				int y = adjustedPosition.y + j;

				int spriteX = i / (scale * zoom);
				int spriteY = j / (scale * zoom);

				unsigned char alpha = image->alphaAtUnchecked(spriteX, spriteY);
				unsigned char* rgb = image->atUnchecked(spriteX, spriteY);

				canvas.DrawPixelUnsafe(x, y, alpha, rgb);
			}
		}
	}

	void DrawBlank(Canvas canvas, Vector<float> offset, float zoom)
	{
		Vector<float> adjustedPosition = (GetTopLeft() - offset) * zoom;

		int xmax = round(min(size.x * zoom, (int)canvas.getWidth() - floor(adjustedPosition.x)));
		int ymax = round(min(size.y * zoom, (int)canvas.getHeight() - floor(adjustedPosition.y)));
		int xmin = round(max(0, -adjustedPosition.x));
		int ymin = round(max(0, -adjustedPosition.y));

		unsigned char alpha = 255;
		unsigned char rgb[3]{ 0, 0, 0 };

		for (int i = xmin; i < xmax; i++)
		{
			int x = adjustedPosition.x + i;

			for (int j = ymin; j < ymax; j++)
			{
				int y = adjustedPosition.y + j;

				canvas.DrawPixelUnsafe(x, y, alpha, rgb);
			}
		}
	}

	//TODO: Implement bilinear
	void DrawBilinear(Canvas canvas, Vector<float> offset, float zoom)
	{
		Vector<float> adjustedPosition = (GetTopLeft() - offset) * zoom;

		int xmax = ceil(min(size.x * zoom + adjustedPosition.x, (int)canvas.getWidth()));
		int ymax = ceil(min(size.y * zoom + adjustedPosition.y, (int)canvas.getHeight()));
		int xmin = floor(max(0, adjustedPosition.x));
		int ymin = floor(max(0, adjustedPosition.y));

		for (int i = xmin; i < xmax; i++)
		{
			for (int j = ymin; j < ymax; j++)
			{
				float spriteX = i - adjustedPosition.x / (zoom * scale);
				float spriteY = j - adjustedPosition.y / (zoom * scale);

				if (spriteX == (int)spriteX && spriteY == (int)spriteY)
				{
					canvas.DrawPixelUnsafe(i, j, image->alphaAtUnchecked(spriteX, spriteY), image->atUnchecked(spriteX, spriteY));
				}
				else
				{
					float x1[3], x2[3], a1, a2;
					float weight = (ceil(spriteX) - spriteX) / (ceil(spriteX) - floor(spriteX));
					unsigned char* pixel = image->atUnchecked(floor(spriteX), floor(spriteY));
					for (int o = 0; o < 3; o++)
					{
						x1[o] += pixel[o] * weight;
					}
					a1 += image->alphaAtUnchecked(floor(spriteX), floor(spriteY)) * weight;
				}
			}
		}
	}

	void Draw(Canvas canvas, Vector<float> offset, float zoom, RenderMethod renderMethod, bool blankIfDisabled = false)
	{
		if (!enabled)
		{
			if (blankIfDisabled)
				DrawBlank(canvas, offset, zoom);
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