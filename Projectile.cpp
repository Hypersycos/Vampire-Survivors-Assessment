#include "Projectile.h"

void Projectile::Update(World* world, InputHandler& input)
{
	Move(movement);
}

void Projectile::Serialize(std::ostream& stream)
{
}

unsigned int Projectile::GetDamage()
{
	return damage;
}

Projectile::Projectile(unsigned int damage, Vector<float> movement, Vector<float> position, GamesEngineeringBase::Image* img, float collisionRadius, CollisionLayer layer) : damage(damage), movement(movement), CollisionSprite(img, position, collisionRadius, layer)
{
}
