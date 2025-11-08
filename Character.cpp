#include "Character.h"
#include "Tile.h"
#include "World.h"

Character::Character() : CollisionSprite()
{
	currentMaxHealth = baseMaxHealth;
	currentSpeed = baseSpeed;
}

Character::Character(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer) : baseMaxHealth(maxHP), health(maxHP), baseSpeed(baseSpeed), CollisionSprite(img, position, collisionBox, layer)
{
	currentSpeed = baseSpeed;
	currentMaxHealth = maxHP;
}

Character::Character(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> collisionBox, CollisionLayer layer) : baseMaxHealth(maxHP), health(maxHP), baseSpeed(baseSpeed), CollisionSprite(img, collisionBox, layer)
{
	currentSpeed = baseSpeed;
	currentMaxHealth = maxHP;
}

int Character::GetHealth() const
{
	return health;
}

int Character::GetMaxHealth() const
{
	return currentMaxHealth;
}

bool Character::Damage(int amount)
{
	health -= max(0, amount);
	return health <= 0;
}

bool Character::Heal(int amount)
{
	health += max(0, amount);
	if (health >= currentMaxHealth)
	{
		health = currentMaxHealth;
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

void Character::TryMove(World* world, Vector<float> move)
{
	if (move.x != 0 || move.y != 0)
	{
		Tile* tile = world->TileAt(position);
		if (tile != nullptr)
			tile->Unapply(this);

		world->TryMove(this, move);

		tile = world->TileAt(position);
		if (tile != nullptr)
			tile->Apply(this);
	}
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
	CollisionSprite::Serialize(stream);
	stream.write(reinterpret_cast<char*>(&currentMaxHealth), sizeof(currentMaxHealth));
	stream.write(reinterpret_cast<char*>(&health), sizeof(health));
	stream.write(reinterpret_cast<char*>(&currentSpeed), sizeof(currentSpeed));
}

void Character::Deserialize(std::istream& stream)
{
	CollisionSprite::Deserialize(stream);
	stream.read(reinterpret_cast<char*>(&currentMaxHealth), sizeof(currentMaxHealth));
	stream.read(reinterpret_cast<char*>(&health), sizeof(health));
	stream.read(reinterpret_cast<char*>(&currentSpeed), sizeof(currentSpeed));
}