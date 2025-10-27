#include "Character.h"

Character::Character() : CollisionSprite()
{

}

Character::Character(int maxHP, float speed, GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer) : maxHealth(maxHP), health(maxHP), speed(speed), CollisionSprite(image, position, collisionRadius, layer)
{
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
	if (health >= maxHealth)
	{
		health = maxHealth;
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
