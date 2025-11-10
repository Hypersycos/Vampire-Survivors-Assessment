#pragma once
#include "Character.h"

//#define GodMode

struct AttackData
{
	float cooldown;
	float currentCooldown;
	int damage;
	float range;

	AttackData(float cooldown, int damage, float range);
	bool ApplyCooldown(float dt, bool attemptingToUse = false);
};

struct ProjectileAttack : AttackData
{
public:
	float baseSpeed;

	ProjectileAttack(float cooldown, int damage, float range, float baseSpeed);
	ProjectileAttack();
};

struct AoEAttack : AttackData
{
	int maxCount;

	AoEAttack(float cooldown, int damage, float range, int maxCount);
	AoEAttack();
};

class Player : public Character
{
	static inline GamesEngineeringBase::Image playerImage{};

	static inline bool imageLoaded = false;

	static GamesEngineeringBase::Image* GetPlayerImage();

	ProjectileAttack autoAttack;

	AoEAttack aoeAttack;

public:
	void Update(World* world, InputHandler& input) override;

	Player();

	void Serialize(std::ostream& stream) override;

	void Deserialize(std::istream& stream) override;

	void Powerup();

#ifdef GodMode
	bool Damage(int amount) override;
#endif

	float GetAoeCooldownPercent();
};