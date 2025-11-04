#pragma once

#include "CollisionSprite.h"

class Projectile : public CollisionSprite
{
	unsigned int damage;
	Vector<float> movement;

public:
	Projectile(unsigned int damage, Vector<float> movement, Vector<float> position, GamesEngineeringBase::Image* img, float collisionRadius, CollisionLayer layer);

	void Update(World* world, InputHandler& input) override;

	void Serialize(std::ostream& stream) override;

	unsigned int GetDamage();
};