#pragma once

#include "CollisionSprite.h"

class Character : public CollisionSprite
{
	int health{ 0 };
	int maxHealth{ 0 };
	float speed{ 0 };
public:
	Character();
	Character(int maxHP, float speed, GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer);
	int GetHealth() const;
	bool Damage(int amount);
	bool Heal(int amount);
	void ChangeHealth(int amount);
};