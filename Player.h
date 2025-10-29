#pragma once
#include "Character.h"

struct AttackData
{
	float cooldown;
	float currentCooldown;
	int damage;
	float range;

	AttackData(float cooldown, int damage, float range) : cooldown(cooldown), damage(damage), range(range), currentCooldown(0)
	{

	}

	bool ApplyCooldown(float dt, bool attemptingToUse = false)
	{
		currentCooldown -= dt;
		if (attemptingToUse && currentCooldown <= 0)
		{
			currentCooldown += cooldown;
			return true;
		}
		else
		{
			currentCooldown = max(0, currentCooldown);
			return false;
		}
	}
};

struct ProjectileAttack : AttackData
{
public:
	float baseSpeed;

	ProjectileAttack(float cooldown, int damage, float range, float baseSpeed) : baseSpeed(baseSpeed), AttackData(cooldown, damage, range)
	{

	}
};

struct AoEAttack : AttackData
{
	int maxCount;

	AoEAttack(float cooldown, int damage, float range, int maxCount) : maxCount(maxCount), AttackData(cooldown, damage, range)
	{

	}
};

class Player : public Character
{
	ProjectileAttack autoAttack{ 1, 5, 32, 64 };

	AoEAttack aoeAttack{ 7, 25, 5, 64 };

public:
	void Update(World* world, InputHandler& input) override;

	Player();

	Player(std::istream& stream);

	void Serialize(std::ostream& stream) override;
};