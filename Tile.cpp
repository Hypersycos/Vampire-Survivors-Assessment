#include "Tile.h"

Tile::Tile(FixedArray<bool, 4> collisionMatrix, FixedArray<float, 4> speedMatrix) : collisionMatrix(collisionMatrix), speedMatrix(speedMatrix)
{
}

void Tile::Apply(Character* character)
{
}

void Tile::Unapply(Character* character)
{
}
