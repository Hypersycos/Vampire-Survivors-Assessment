#include "Character.h"

Character::Character() : CollisionSprite()
{
	currentMaxHealth = baseMaxHealth;
	currentSpeed = baseSpeed;
}

Character::Character(int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer) : baseMaxHealth(maxHP), health(maxHP), baseSpeed(baseSpeed), CollisionSprite(image, position, collisionRadius, layer)
{
	currentSpeed = baseSpeed;
	currentMaxHealth = baseMaxHealth;
}

int Character::GetHealth() const
{
	return health;
}

bool Character::Damage(int amount)
{
	health -= max(0, amount);
	return health <= 0;
}

bool Character::Heal(int amount)
{
	health += max(0, amount);
	if (health >= baseMaxHealth)
	{
		health = baseMaxHealth;
		return true;
	}
	else
	{
		return false;
	}
}

void Character::ChangeHealth(int amount)
{
	health += amount;
}
