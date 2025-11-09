#pragma once

#include "Projectile.h"

class PlayerProjectile : public Projectile
{
	static inline GamesEngineeringBase::Image playerProjectileImage{};

	static inline bool imageLoaded = false;

	static GamesEngineeringBase::Image* GetImage();

public:
	PlayerProjectile(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime);
	PlayerProjectile(std::istream& stream);
};