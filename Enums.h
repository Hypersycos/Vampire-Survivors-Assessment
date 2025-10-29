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
	Unset = -1,
	CollidesWithPlayer = 0,
	CollidesWithEnemies = 1,
	CollidesWithPlayerProjectiles = 2,
	CollidesWithEnemyProjectiles = 3
};

#endif