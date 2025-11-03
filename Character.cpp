#include "Character.h"

Character::Character() : CollisionSprite()
{
	currentMaxHealth = baseMaxHealth;
	currentSpeed = baseSpeed;
}

Character::Character(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer) : baseMaxHealth(maxHP), health(maxHP), baseSpeed(baseSpeed), CollisionSprite(img, position, collisionRadius, layer)
{
	currentSpeed = baseSpeed;
	currentMaxHealth = maxHP;
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

void Character::SetSpeedScalar(float s)
{
	currentSpeed = baseSpeed * s;
}

void Character::SetHealthScalar(float s)
{
	currentMaxHealth = (unsigned int)round(baseMaxHealth * s);
}

void Character::Serialize(std::ostream& stream)
{
	stream << currentMaxHealth << health << currentSpeed;
}

Character::Character(std::istream& stream) : CollisionSprite(stream)
{
	stream >> currentMaxHealth;
	stream >> health;
	stream >> currentSpeed;
}
