#pragma once

enum RenderMethod
{
	Integer,
	Bilinear,
	Blank
};

enum CollisionLayer
{
	CollidesWithPlayer = 1,
	CollidesWithEnemies = 2
};