#pragma once

#include "GamesEngineeringBase.h"
#include "Vector.h"

#pragma once

class Canvas
{
	GamesEngineeringBase::Window& canvas;
	Vector<unsigned int> size;
	Vector<unsigned int> position;

public:
	Canvas(GamesEngineeringBase::Window& canvas, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	Canvas(GamesEngineeringBase::Window& canvas, Vector<unsigned int> size, Vector<unsigned int> position);

	Vector<unsigned int> GetSize();

	unsigned int getWidth();

	unsigned int getHeight();

	void clear();

	void DrawPixelUnsafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb);

	void DrawPixelSafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb);

	void DrawBoxUnsafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b);

	void DrawBoxSafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b);
};