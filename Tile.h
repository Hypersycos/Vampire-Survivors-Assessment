#pragma once
#include "GamesEngineeringBase.h"
#include "FixedArray.h"
#include "Character.h"

class Tile
{
public:
	FixedArray<bool, 4> collisionMatrix;
	FixedArray<float, 4> speedMatrix;
	GamesEngineeringBase::Image image;

	Tile(FixedArray<bool, 4> collisionMatrix, FixedArray<float, 4> speedMatrix);

	void Apply(Character* character);
	void Unapply(Character* character);
};