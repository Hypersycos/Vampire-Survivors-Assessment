#pragma once

#include "GamesEngineeringBase.h"
#include "Vector.h"

#include "Image.h"
//#define enableDrawBeyondBounds

#pragma once

class Canvas
{
	GamesEngineeringBase::Window& canvas;
	Vector<unsigned int> size;
	Vector<unsigned int> position;

public:

	enum RenderMethod
	{
		Integer,
		NearestInteger,
		Bilinear,
		Blank
	};

	Canvas(GamesEngineeringBase::Window& canvas, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	Canvas(GamesEngineeringBase::Window& canvas, Vector<unsigned int> size, Vector<unsigned int> position);

	Vector<unsigned int> GetSize();

	unsigned int getWidth() const;

	unsigned int getHeight() const;

	Vector<unsigned int> GetPosition();

	unsigned int getXPos() const;

	unsigned int getYPos() const;

	void clear();

	void DrawPixelUnsafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb);

	void DrawPixelSafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb);

	void DrawBoxUnsafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b);

	void DrawBoxSafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b);

	void DrawFilledBoxSafe(unsigned char* rgb, unsigned char alpha, Vector<float> position, Vector<float> size);

	void DrawFilledBoxUnsafe(unsigned char* rgb, unsigned char alpha, Vector<float> position, Vector<float> size);

	void GetValues(int& xmin, int& xmax, int& ymin, int& ymax, Vector<float>& position, Vector<float>& imageOffset, Vector<float>& imageSize, float& scale) const;

	void Draw(ImageSet& img, Vector<float> canvasPosition, Vector<float> imageSize, Vector<float> imageOffset, float scale = 1, RenderMethod render = Integer);

	void DrawInteger(ImageSet& img, Vector<float> position, Vector<float> imageSize, Vector<float> imageOffset, float scale = 1);

	void DrawBilinear(ImageSet& img, Vector<float> position, Vector<float> imageSize, Vector<float> imageOffset, float scale = 1);

	void DrawFont(std::string text, Vector<float> position, float scale = 1, RenderMethod render = Integer, Colour c = {255, 255, 255, 255});
};