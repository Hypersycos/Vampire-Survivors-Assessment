#include "GamesEngineeringBase.h"
#include "Vector.cpp"

#pragma once

class Canvas
{
	GamesEngineeringBase::Window& canvas;
	Vector<unsigned int> size;
	Vector<unsigned int> position;

public:
	Canvas(GamesEngineeringBase::Window& canvas, unsigned int width, unsigned int height, unsigned int x, unsigned int y) : canvas(canvas)
	{
		size = Vector<unsigned int>(width, height);
		position = Vector<unsigned int>(x, y);
	}

	Canvas(GamesEngineeringBase::Window& canvas, Vector<unsigned int> size, Vector<unsigned int> position) : size(size), position(position), canvas(canvas)
	{

	}

	Vector<unsigned int> GetSize()
	{
		return size;
	}

	unsigned int getWidth()
	{
		return size.x;
	}

	unsigned int getHeight()
	{
		return size.y;
	}

	void clear()
	{
#ifdef enableDrawBeyondBounds
		canvas.clear();
#else
		//for (int i = 0; i < size.y; i++)
		//{
		//	memset(canvas.backBuffer() + (position.x) * (i + 1) + canvas.getWidth() * i, 0, size.x * 3 * sizeof(unsigned char));
		//}
		unsigned char rgb[3]{ 0, 0, 0 };
		for (int i = 0; i < size.x; i++)
		{
			for (int j = 0; j < size.y; j++)
			{
				DrawPixelUnsafe(i, j, 255, rgb);
			}
		}
#endif
	}

	void DrawPixelUnsafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb)
	{
		x += position.x;
		y += position.y;
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

	void DrawPixelSafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb)
	{
		if (x >= size.x || y >= size.y)
			return;
		DrawPixelUnsafe(x, y, alpha, rgb);
	}

	void DrawBoxUnsafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b)
	{
		topLeft += position;
		botRight += position;
		for (int i = topLeft.x; i <= botRight.x; i++)
		{
			canvas.draw(i, topLeft.y, r, g, b);
			canvas.draw(i, botRight.y, r, g, b);
		}

		for (int i = topLeft.y; i <= botRight.y; i++)
		{
			canvas.draw(topLeft.x, i, r, g, b);
			canvas.draw(botRight.x, i, r, g, b);
		}
	}

	void DrawBoxSafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b)
	{
		if (topLeft.x >= size.x || topLeft.y >= size.y
			|| botRight.x >= size.x || botRight.y >= size.y
			|| topLeft.x > botRight.x || topLeft.y > botRight.y)
			return;
		DrawBoxUnsafe(topLeft, botRight, r, g, b);
	}
};