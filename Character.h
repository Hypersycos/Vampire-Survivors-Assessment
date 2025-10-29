#pragma once

#include "CollisionSprite.h"

class Character : public CollisionSprite
{
protected:
	int health{ 0 };

	int baseMaxHealth{ 0 };
	int currentMaxHealth;

	float baseSpeed{ 0 };
	float currentSpeed;
public:
	Character();
	Character(int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer);
	int GetHealth() const;
	bool Damage(int amount);
	bool Heal(int amount);
	void ChangeHealth(int amount);
};