#pragma once

#include "CollisionSprite.h"

class Character : public CollisionSprite
{
protected:
	int health{ 0 };

	unsigned int baseMaxHealth{ 0 };
	unsigned int currentMaxHealth;

	float baseSpeed{ 0 };
	float currentSpeed;
public:
	Character();
	Character(std::istream& stream);
	Character(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer);
	Character(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> collisionBox, CollisionLayer layer);
	int GetHealth() const;
	bool Damage(int amount);
	bool Heal(int amount);
	void ChangeHealth(int amount);
	void TryMove(World* world, Vector<float> move);

	void SetSpeedScalar(float s);
	void SetHealthScalar(float s);

	void Serialize(std::ostream& stream) override;
};