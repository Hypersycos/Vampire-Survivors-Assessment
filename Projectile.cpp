#include "Projectile.h"

void Projectile::Update(World* world, InputHandler& input)
{
	Move(movement);
}

void Projectile::Serialize(std::ostream& stream)
{
}
