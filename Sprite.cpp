#include "GamesEngineeringBase.h"
#include "Vector.cpp"
#include "Enums.cpp"

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

	void DrawPixel(GamesEngineeringBase::Window& canvas, unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb)
	{
		if (alpha == 0)
			return;
		else if (alpha < 255)
		{
			//handles partial transparency by adding back buffer and sprite values together
			//weighted by (255 - alpha) and alpha respectively
			int bAlpha = 255 - alpha;

			unsigned char* backBuffer = canvas.getBackBuffer();
			int pixelIndex = ((y * canvas.getWidth()) + x) * 3;
			unsigned char* pixel = &backBuffer[pixelIndex];

			unsigned char alphaPixel[3];
			alphaPixel[0] = (pixel[0] * bAlpha) / 255 + (rgb[0] * alpha) / 255;
			alphaPixel[1] = (pixel[1] * bAlpha) / 255 + (rgb[1] * alpha) / 255;
			alphaPixel[2] = (pixel[2] * bAlpha) / 255 + (rgb[2] * alpha) / 255;
			canvas.draw(x, y, alphaPixel);
		}
		else
			canvas.draw(x, y, rgb);
	}

	void DrawInteger(GamesEngineeringBase::Window& canvas, Vector<float> offset, float zoom)
	{
		Vector<float> adjustedPosition = (GetTopLeft() - offset) * zoom;

		int xmax = round(min(size.x * zoom, (int)canvas.getWidth() - adjustedPosition.x));
		int ymax = round(min(size.y * zoom, (int)canvas.getHeight() - adjustedPosition.y));
		int xmin = round(max(0, -adjustedPosition.x));
		int ymin = round(max(0, -adjustedPosition.y));

		for (int i = xmin; i < xmax; i++)
		{
			int x = adjustedPosition.x + i;

			for (int j = ymin; j < ymax; j++)
			{
				int y = adjustedPosition.y + j;

				int spriteX = i / (scale * zoom);
				int spriteY = j / (scale * zoom);

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

	void DrawBilinear(GamesEngineeringBase::Window& canvas, Vector<float> offset, float zoom)
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
					DrawPixel(canvas, i, j, image->alphaAtUnchecked(spriteX, spriteY), image->atUnchecked(spriteX, spriteY));
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

	void Draw(GamesEngineeringBase::Window& canvas, Vector<float> offset, float zoom, RenderMethod renderMethod)
	{
		if (!enabled)
			return;

		switch (renderMethod)
		{
		case Integer:
			DrawInteger(canvas, offset, zoom);
			break;
		default:
			break;
		}
	}
};