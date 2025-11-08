#include "Canvas.h"
#include "font.h"

Canvas::Canvas(GamesEngineeringBase::Window& canvas, unsigned int width, unsigned int height, unsigned int x, unsigned int y) : canvas(canvas)
{
	size = Vector<unsigned int>(width, height);
	position = Vector<unsigned int>(x, y);
}

Canvas::Canvas(GamesEngineeringBase::Window& canvas, Vector<unsigned int> size, Vector<unsigned int> position) : size(size), position(position), canvas(canvas)
{

}

Vector<unsigned int> Canvas::GetSize()
{
	return size;
}

unsigned int Canvas::getWidth() const
{
	return size.x;
}

unsigned int Canvas::getHeight() const
{
	return size.y;
}

void Canvas::clear()
{
#ifdef enableDrawBeyondBounds
	canvas.clear();
#else
	for (unsigned int i = 0; i < size.y; i++)
	{
		memset(canvas.backBuffer() + (position.x + canvas.getWidth() * i) * 3, 0, size.x * 3 * sizeof(unsigned char));
	}

	//unsigned char rgb[3]{ 0, 0, 0 };
	//for (unsigned int i = 0; i < size.x; i++)
	//{
	//	for (unsigned int j = 0; j < size.y; j++)
	//	{
	//		DrawPixelUnsafe(i, j, 255, rgb);
	//	}
	//}
#endif
}

void Canvas::DrawPixelUnsafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb)
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

		unsigned char alphaPixel[3] = {};
		alphaPixel[0] = (pixel[0] * bAlpha) / 255 + (rgb[0] * alpha) / 255;
		alphaPixel[1] = (pixel[1] * bAlpha) / 255 + (rgb[1] * alpha) / 255;
		alphaPixel[2] = (pixel[2] * bAlpha) / 255 + (rgb[2] * alpha) / 255;
		canvas.draw(x, y, alphaPixel);
	}
	else
		canvas.draw(x, y, rgb);
}

void Canvas::DrawPixelSafe(unsigned int x, unsigned int y, unsigned char alpha, unsigned char* rgb)
{
	if (x >= size.x || y >= size.y)
		return;
	DrawPixelUnsafe(x, y, alpha, rgb);
}

void Canvas::DrawBoxUnsafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b)
{
	topLeft += position;
	botRight += position;
	for (unsigned int i = topLeft.x; i <= botRight.x; i++)
	{
		canvas.draw(i, topLeft.y, r, g, b);
		canvas.draw(i, botRight.y, r, g, b);
	}

	for (unsigned int i = topLeft.y; i <= botRight.y; i++)
	{
		canvas.draw(topLeft.x, i, r, g, b);
		canvas.draw(botRight.x, i, r, g, b);
	}
}

void Canvas::DrawBoxSafe(Vector<unsigned int> topLeft, Vector<unsigned int> botRight, unsigned char r, unsigned char g, unsigned char b)
{
	if (topLeft.x >= size.x || topLeft.y >= size.y
		|| botRight.x >= size.x || botRight.y >= size.y
		|| topLeft.x > botRight.x || topLeft.y > botRight.y)
		return;
	DrawBoxUnsafe(topLeft, botRight, r, g, b);
}

#define getIntPos(position) Vector<int>(position)

void Canvas::DrawFilledBoxUnsafe(unsigned char* rgb, unsigned char alpha, Vector<float> position, Vector<float> size)
{
	Vector<int> intPos = getIntPos(position);

	for (int i = 0; i < round(size.x); i++)
	{
		int x = intPos.x + i;

		for (int j = 0; j < round(size.y); j++)
		{
			int y = intPos.y + j;

			DrawPixelUnsafe(x, y, alpha, rgb);
		}
	}
}

void Canvas::DrawFilledBoxSafe(unsigned char* rgb, unsigned char alpha, Vector<float> position, Vector<float> size)
{
	if (position.x <= 0)
	{
		size.x += position.x;
		position.x = 0;
	}
	if (position.y <= 0)
	{
		size.y += position.y;
		position.y = 0;
	}
	if ((float)getWidth() - (position.x + size.x) <= 0)
	{
		size.x += (float)getWidth() - (position.x + size.x);
	}
	if ((float)getHeight() - (position.y + size.y) <= 0)
	{
		size.y += (float)getHeight() - (position.y + size.y);
	}
	DrawFilledBoxUnsafe(rgb, alpha, position, size);
}

void Canvas::GetValues(int& xmin, int& xmax, int& ymin, int& ymax, Vector<float>& position, Vector<float>& imageOffset, Vector<float>& imageSize, float& scale) const
{
	position -= imageOffset * scale;
#ifdef enableDrawBeyondBounds
	xmax = round(imageSize.x);
	ymax = round(imageSize.y);
	xmin = round(imageOffset.x);
	ymin = round(imageOffset.y);
#else
	xmax = min((int)round(imageSize.x + imageOffset.x), (int)size.x - (int)floor(position.x));
	ymax = min((int)round(imageSize.y + imageOffset.y), (int)size.y - (int)floor(position.y));
	xmin = (int)round(max(round(imageOffset.x), -position.x));
	ymin = (int)round(max(round(imageOffset.y), -position.y));
#endif // enableDrawBeyondBounds
}

void Canvas::DrawInteger(GamesEngineeringBase::Image* image, Vector<float> position, Vector<float> imageSize, Vector<float> imageOffset, float scale)
{
	Vector<int> intPos = getIntPos(position);

	int xmin, xmax, ymin, ymax;
	GetValues(xmin, xmax, ymin, ymax, position, imageOffset, imageSize, scale);

	for (int i = xmin; i < xmax; i++)
	{
		int x = intPos.x + i - round(imageOffset.x);

		for (int j = ymin; j < ymax; j++)
		{
			int y = intPos.y + j - round(imageOffset.y);

			int spriteX = (int)(i / scale);
			int spriteY = (int)(j / scale);

			unsigned char alpha = image->alphaAtUnchecked(spriteX, spriteY);
			unsigned char* rgb = image->atUnchecked(spriteX, spriteY);

			DrawPixelUnsafe(x, y, alpha, rgb);
		}
	}
}

//TODO: Implement bilinear
void Canvas::DrawBilinear(GamesEngineeringBase::Image* image, Vector<float> position, Vector<float> imageSize, Vector<float> imageOffset, float scale)
{
	//int xmax = min((int)round(image->width * scale), (int)size.x - (int)floor(position.x));
	//int ymax = min((int)round(image->height * scale), (int)size.y - (int)floor(position.y));
	//int xmin = (int)round(max(0, -position.x));
	//int ymin = (int)round(max(0, -position.y));

	//for (int i = xmin; i < xmax; i++)
	//{
	//	float spriteX = i - position.x / scale;
	//	for (int j = ymin; j < ymax; j++)
	//	{
	//		float spriteY = j - position.y / scale;

	//		if (spriteX == round(spriteX) && spriteY == round(spriteY))
	//		{
	//			DrawPixelUnsafe(i, j, image->alphaAtUnchecked(spriteX, spriteY), image->atUnchecked(spriteX, spriteY));
	//		}
	//		else
	//		{
	//			float x1[3], x2[3], a1, a2;
	//			float weight = (ceil(spriteX) - spriteX) / (ceil(spriteX) - floor(spriteX));
	//			unsigned char* pixel = image->atUnchecked(floor(spriteX), floor(spriteY));
	//			for (int o = 0; o < 3; o++)
	//			{
	//				x1[o] += pixel[o] * weight;
	//			}
	//			a1 += image->alphaAtUnchecked(floor(spriteX), floor(spriteY)) * weight;
	//		}
	//	}
	//}
}

void Canvas::DrawFont(std::string text, Vector<float> position, float scale, RenderMethod render)
{
	Vector<int> letterSize = Font::letterSize;
	int xSize = letterSize.x + Font::xGap;
	GamesEngineeringBase::Image* image = Font::GetImage();

	for (char c : text)
	{
		Vector<int> offset = Font::GetLetterLocation(c);
		Draw(image, position, letterSize, offset, scale, render);
		position.x += xSize;
	}
}

void Canvas::Draw(GamesEngineeringBase::Image* image, Vector<float> position, Vector<float> imageSize, Vector<float> imageOffset, float scale, RenderMethod render)
{
	switch (render)
	{
	case Integer:
		DrawInteger(image, position, imageSize, imageOffset, scale);
		break;
	case Bilinear:
		//DrawBilinear(image, position, imageSize, imageOffset, scale);
		break;
	case Blank:
	{
		unsigned char rgb[3] = { 0, 0, 0 };
#ifdef enableDrawBeyondBounds
		DrawFilledBoxUnsafe(rgb, 255, position, imageSize);
#else
		DrawFilledBoxSafe(rgb, 255, position, imageSize);
#endif
	}
		break;
	default:
		break;
	}
}