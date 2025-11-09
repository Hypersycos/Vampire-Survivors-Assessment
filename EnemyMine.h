#pragma once

#include "Projectile.h"

class EnemyMine : public Projectile
{
	static inline GamesEngineeringBase::Image enemyProjectileImage{};

	static inline bool imageLoaded = false;

	static GamesEngineeringBase::Image* GetImage();

	float movementTime;

public:
	EnemyMine(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime, float moveTime);
	EnemyMine(std::istream& stream);

	void Update(World* world, InputHandler& input) override;

	void Serialize(std::ostream& stream) override;

	void Deserialize(std::istream& stream) override;
};