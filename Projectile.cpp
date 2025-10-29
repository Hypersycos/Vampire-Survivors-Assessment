#include "Projectile.h"

void Projectile::Update(World* world, InputHandler& input)
{
	Move(movement);
}