#pragma once

struct Colour
{
	unsigned char colour[3];
	unsigned char alpha;

	Colour(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255) : alpha(alpha)
	{
		colour[0] = r;
		colour[1] = g;
		colour[2] = b;
	}

	Colour() : Colour(0, 0, 0, 255)
	{

	}
};