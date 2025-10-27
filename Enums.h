#pragma once
#ifndef ENUMS
#define ENUMS

enum RenderMethod
{
	Integer,
	NearestInteger
	Bilinear,
	Blank
};
#endif
};

enum CollisionLayer
{
	CollidesWithPlayer = 1,
	CollidesWithEnemies = 2
};