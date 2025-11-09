#include "Image.h"


Image::Image() : colourMult{ 255, 255, 255, 255 }, image(nullptr)
{

}
Image::Image(GamesEngineeringBase::Image* image) : colourMult{ 255, 255, 255, 255 }
{
	SetImage(image);
}
Image::Image(GamesEngineeringBase::Image* image, Colour c) : colourMult(c)
{
	SetImage(image);
}

Image::Image(const Image& copy)
{
	colourMult = copy.colourMult;
	SetImage(copy.image);
}

void Image::SetImage(GamesEngineeringBase::Image* image)
{
	this->image = image;
	width = image->width;
	height = image->height;
}


Colour Image::atUnchecked(unsigned int x, unsigned int y)
{
	unsigned char* c = this->image->atUnchecked(x, y);
	unsigned char r = (c[0] * colourMult.colour[0]) / 255;
	unsigned char g = (c[1] * colourMult.colour[1]) / 255;
	unsigned char b = (c[2] * colourMult.colour[2]) / 255;
	unsigned char a = (this->image->alphaAtUnchecked(x, y) * colourMult.alpha) / 255;
	return Colour{ r, g, b, a };
}

bool Image::isValidPixel(unsigned int x, unsigned int y)
{
	return x >= 0 && x < width && y >= 0 && y < height;
}


ImageSet::ImageSet() : colourMult{255, 255, 255, 255}
{

}

ImageSet::ImageSet(std::initializer_list<Image> images) : images{images}, colourMult { 255, 255, 255, 255 }
{
	
}

ImageSet::ImageSet(std::initializer_list<GamesEngineeringBase::Image*> images) : images{ 1 }, colourMult{ 255, 255, 255, 255 }
{
	for (GamesEngineeringBase::Image* img : images)
	{
		this->images.Add(img);
	}
}

ImageSet::ImageSet(ImageSet& copy) : colourMult{ 255, 255, 255, 255 }
{
	for (const Image& img : copy.images)
	{
		images.Add(img);
	}
}

ImageSet& ImageSet::operator=(ImageSet& o)
{
	for (const Image& img : o.images)
	{
		images.Add(img);
	}
	colourMult = o.colourMult;
	return *this;
}

void ImageSet::ChangeImage(unsigned int i)
{
	int img = ((int)currentImage + (int)i) % (int)images.GetCurrentSize();
	if (img < 0)
	{
		img += images.GetCurrentSize();
	}
	currentImage = img;
}

void ImageSet::SetImage(unsigned int i)
{
	currentImage = i % (int)images.GetCurrentSize();
}

Image& ImageSet::GetImage()
{
	return images[currentImage];
}

void ImageSet::AddImage(GamesEngineeringBase::Image* image)
{
	images.Add(Image(image));
}

Vector<unsigned int> ImageSet::GetSize()
{
	return Vector<unsigned int>(GetImage().width, GetImage().height);
}
unsigned int ImageSet::GetWidth()
{
	return GetImage().width;
}
unsigned int ImageSet::GetHeight()
{
	return GetImage().height;
}

Colour ImageSet::atUnchecked(unsigned int x, unsigned int y)
{
	Colour c = GetImage().atUnchecked(x, y);
	unsigned char r = (c.colour[0] * colourMult.colour[0]) / 255;
	unsigned char g = (c.colour[1] * colourMult.colour[1]) / 255;
	unsigned char b = (c.colour[2] * colourMult.colour[2]) / 255;
	unsigned char a = (c.alpha * colourMult.alpha) / 255;
	return Colour{ r, g, b, a };
}

bool ImageSet::isValidPixel(unsigned int x, unsigned int y)
{
	return GetImage().isValidPixel(x, y);
}