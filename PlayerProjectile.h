#pragma once

#include "Projectile.h"

class PlayerProjectile : public Projectile
{
public:
	PlayerProjectile(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime);
	PlayerProjectile(std::istream& stream);
};