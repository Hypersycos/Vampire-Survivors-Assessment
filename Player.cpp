#pragma once

#include "Sprite.cpp"
#include "InputHandler.cpp"

struct AttackData
{
	float cooldown;
	float currentCooldown;
	int damage;
	float range;

	AttackData(float cooldown, int damage, float range) : cooldown(cooldown), damage(damage), range(range)
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
	float speed;

	ProjectileAttack(float cooldown, int damage, float range, float speed) : speed(speed), AttackData(cooldown, damage, range)
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

//float GetEnemyHealth(Enemy* enemy)
//{
//	return enemy->GetHealth();
//}

class Player : public Sprite
{
	ProjectileAttack autoAttack { 1, 5, 32, 64 };

	AoEAttack aoeAttack{ 7, 25, 5, 64 };

	//void Update(float dt, World* world, InputHandler& input) override
	//{
	//	bool doAoE = aoeAttack.ApplyCooldown(dt, input.KeyDown(' '));

	//	Enemy* nearest = world->GetNearestEnemyToPlayer(autoAttack.range);
	//	bool doAttack = autoAttack.ApplyCooldown(dt, nearest != nullptr);

	//	if (doAttack)
	//	{
	//		//spawn projectile
	//	}

	//	if (doAoE)
	//	{
	//		Array<Enemy*> aoeEnemies = Array<Enemy>(aoeAttack.maxCount);
	//		world->GetNearestNEnemiesToPlayer(aoeAttack.maxCount, aoeEnemies, GetEnemyHealth);
	//		for (Enemy* e : aoeEnemies)
	//		{
	//			if (e != nullptr)
	//			{
	//				//damage e
	//			}
	//		}
	//	}
	//}
};