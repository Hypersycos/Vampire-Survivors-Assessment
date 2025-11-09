#pragma once

struct Colour
{
	unsigned char color[3];
	unsigned char alpha;

	Colour(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255) : alpha(alpha)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
};