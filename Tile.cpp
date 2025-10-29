#include "Tile.h"

Tile::Tile(FixedArray<bool, 4> collisionMatrix, FixedArray<float, 2> speedMatrix) : collisionMatrix(collisionMatrix), speedMatrix(speedMatrix)
{
}

void Tile::Apply(Character* character)
{
	character->SetSpeedScalar(speedMatrix[character->getLayer()]);
}

void Tile::Unapply(Character* character)
{
}
