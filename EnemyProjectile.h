#pragma once

#include "Projectile.h"

class EnemyProjectile : public Projectile
{
public:
	EnemyProjectile(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime);
	EnemyProjectile(std::istream& stream);
};