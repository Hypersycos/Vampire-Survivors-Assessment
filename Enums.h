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
	CollidesWithPlayer = 1,
	CollidesWithEnemies = 2
};

#endif