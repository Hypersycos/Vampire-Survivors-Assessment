#pragma once
#include "DynamicArray.h"
#include "Vector.h"
#include "GamesEngineeringBase.h"
#include "Colour.h"
class Image
{
public:
	Image();
	Image(GamesEngineeringBase::Image* image);
	Image(GamesEngineeringBase::Image* image, Colour mult);
	Image(const Image& copy);

	GamesEngineeringBase::Image* image;
	Colour colourMult;

	void SetImage(GamesEngineeringBase::Image* image);

	unsigned int width{ 0 };
	unsigned int height{ 0 };

	Colour atUnchecked(unsigned int x, unsigned int y);

	bool isValidPixel(unsigned int x, unsigned int y);
};

class ImageSet
{
	DynamicArray<Image> images;
	unsigned int currentImage{ 0 };

	unsigned int width{ 0 };
	unsigned int height{ 0 };

public:
	Colour colourMult;

	ImageSet();
	ImageSet(std::initializer_list<Image> images);
	ImageSet(std::initializer_list<GamesEngineeringBase::Image*> images);
	ImageSet(ImageSet& copy);

	ImageSet& operator=(ImageSet& o);

	void ChangeImage(unsigned int i = 1);
	void SetImage(unsigned int i);
	Image& GetImage();
	void AddImage(GamesEngineeringBase::Image* image);
	Vector<unsigned int> GetSize();
	unsigned int GetWidth();
	unsigned int GetHeight();

	Colour atUnchecked(unsigned int x, unsigned int y);

	bool isValidPixel(unsigned int x, unsigned int y);
};