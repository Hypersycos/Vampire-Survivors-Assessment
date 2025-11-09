#pragma once

#include "Projectile.h"

class EnemyProjectile : public Projectile
{
	static inline GamesEngineeringBase::Image enemyProjectileImage{};

	static inline bool imageLoaded = false;

	static GamesEngineeringBase::Image* GetImage();

public:
	EnemyProjectile(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime);
	EnemyProjectile(std::istream& stream);

	void Serialize(std::ostream& stream) override;
};