#include "Projectile.h"
#include "World.h"

void Projectile::Update(World* world, InputHandler& input)
{
	Move(movement * input.GetDT());
	lifetime -= input.GetDT();
	if (lifetime <= 0)
		enabled = false;
}

void Projectile::Serialize(std::ostream& stream)
{
}

unsigned int Projectile::GetDamage()
{
	return damage;
}

Projectile::Projectile(unsigned int damage, Vector<float> movement, Vector<float> position, GamesEngineeringBase::Image* img, Vector<float> collisionBox, CollisionLayer layer, float lifetime) : damage(damage), movement(movement), CollisionSprite(img, position, collisionBox, layer), lifetime(lifetime)
{
}
