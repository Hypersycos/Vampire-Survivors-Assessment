#pragma once

#include "GamesEngineeringBase.h"
#include "Vector.h"
#include "Enums.h"
//#define enableDrawBeyondBounds

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

	unsigned int getWidth() const;

	unsigned int getHeight() const;

	void clear();

	void DrawPixelUnsafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb);

	void DrawPixelSafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb);

	void DrawBoxUnsafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b);

	void DrawBoxSafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b);

	void DrawFilledBoxSafe(unsigned char* rgb, unsigned char alpha, Vector<float> position, Vector<float> size);

	void DrawFilledBoxUnsafe(unsigned char* rgb, unsigned char alpha, Vector<float> position, Vector<float> size);

	void GetValues(int& xmin, int& xmax, int& ymin, int& ymax, Vector<float>& position, Vector<float>& imageOffset, Vector<float>& imageSize, float& scale) const;

	void Draw(GamesEngineeringBase::Image* image, Vector<float> canvasPosition, Vector<float> imageSize, Vector<float> imageOffset, float scale = 1, RenderMethod render = Integer);

	void DrawInteger(GamesEngineeringBase::Image* image, Vector<float> position, Vector<float> imageSize, Vector<float> imageOffset, float scale = 1);

	void DrawBilinear(GamesEngineeringBase::Image* image, Vector<float> position, Vector<float> imageSize, Vector<float> imageOffset, float scale = 1);
};