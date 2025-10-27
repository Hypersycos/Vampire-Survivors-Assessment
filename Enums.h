#pragma once
#ifndef ENUMS
#define ENUMS

enum RenderMethod
{
	Integer,
	NearestInteger,
	Bilinear,
	Blank
};

enum CollisionLayer
{
	Unset = 0,
	CollidesWithPlayer = 1,
	CollidesWithEnemies = 2
};

#endif