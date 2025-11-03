#pragma once

#include "Character.h"
#include "EnemyImageHolder.h"

class Enemy : public Character
{
protected:
	Vector<float> Pathfind(World* world, float dt);

public:
	inline static EnemyImageHolder ImageHolder;

	Enemy(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer = CollidesWithPlayerProjectiles);

	void Update(World* world, InputHandler& input) override;
};