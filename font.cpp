#include "font.h"

Image& Font::GetImage()
{
	if (!imageLoaded)
	{
		fontImage.load("Resources/font.png");
		img.SetImage(&fontImage);
		imageLoaded = true;
	}
	return img;
}

Vector<int> Font::GetLetterLocation(char l)
{
	if (97 <= l && l <= 122)
	{
		int offset = l - 97;
		return Vector<int>{(letterSize.x + xGap)* offset, 0};
	}
	else if (65 <= l && l <= 90)
	{
		int offset = l - 65;
		return Vector<int>{(letterSize.x + xGap)* offset, letterSize.y + yGap};
	}
	else if (42 <= l && l <= 63)
	{
		int offset = l - 42;
		return Vector<int>{(letterSize.x + xGap)* offset, (letterSize.y + yGap) * 2};
	}
	else if (l == 33)
		return Vector<int>{(letterSize.x + xGap) * 22, (letterSize.y + yGap) * 2};
	else if (l == 34)
		return Vector<int>{(letterSize.x + xGap) * 23, (letterSize.y + yGap) * 2};
	else if (l == 39)
		return Vector<int>{(letterSize.x + xGap) * 24, (letterSize.y + yGap) * 2};
	else
		return Vector<int>{(letterSize.x + xGap) * 25, (letterSize.y + yGap) * 2};
}