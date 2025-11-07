#include "Player.h"
#include "Enemy.h"
#include "World.h"

AttackData::AttackData(float cooldown, int damage, float range) : cooldown(cooldown), damage(damage), range(range), currentCooldown(0)
{

}

bool AttackData::ApplyCooldown(float dt, bool attemptingToUse)
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

ProjectileAttack::ProjectileAttack(float cooldown, int damage, float range, float baseSpeed) : baseSpeed(baseSpeed), AttackData(cooldown, damage, range)
{

}

ProjectileAttack::ProjectileAttack() : ProjectileAttack{ 1, 5, 384, 512 }
{
}

AoEAttack::AoEAttack(float cooldown, int damage, float range, int maxCount) : maxCount(maxCount), AttackData(cooldown, damage, range)
{

}

AoEAttack::AoEAttack() : AoEAttack{ 4, 15, 256, 3 }
{
}

static float GetEnemyHealth(Enemy* enemy)
{
	return (float)enemy->GetHealth();
}

Player::Player() : Character(100, 200, nullptr, Vector<float>(0, 0), Vector<float>(32, 32), CollidesWithEnemyProjectiles)
{
}

void Player::Serialize(std::ostream& stream)
{
	stream << aoeAttack.currentCooldown << autoAttack.currentCooldown;
}

Player::Player(std::istream& stream) : Character(stream)
{
	stream >> aoeAttack.currentCooldown;
	stream >> autoAttack.currentCooldown;
}

void Player::Update(World* world, InputHandler& input)
{
	CollisionSprite::Update(world, input);
	bool doAoE = aoeAttack.ApplyCooldown(input.GetDT(), input.KeyDown(' '));

	Enemy* nearest = world->GetNearestEnemyToPlayer(autoAttack.range);
	bool doAttack = autoAttack.ApplyCooldown(input.GetDT(), nearest != nullptr);

	if (doAttack)
	{
		Projectile* p = new Projectile(autoAttack.damage, (nearest->GetPosition() - position).scaleTo(autoAttack.baseSpeed), position, &Tile::GetTile(2)->image, Vector<float>(32, 32), CollidesWithEnemies, 3);
		world->SpawnProjectile(p);
	}
 
	if (doAoE)
	{
		Array<Enemy*> aoeEnemies = Array<Enemy*>(aoeAttack.maxCount);
		world->GetNearestNEnemiesToPlayer(aoeAttack.range, aoeEnemies, GetEnemyHealth);
		for (Enemy* e : aoeEnemies)
		{
			if (e != nullptr)
			{
				e->Damage(aoeAttack.damage);
			}
		}
	}

	Vector<float> movement = Vector<float>();

	if (input.KeyHeld('W'))
	{
		movement.y -= 1;
	}
	if (input.KeyHeld('A'))
	{
		movement.x -= 1;
	}
	if (input.KeyHeld('S'))
	{
		movement.y += 1;
	}
	if (input.KeyHeld('D'))
	{
		movement.x += 1;
	}

	if (movement.x != 0 || movement.y != 0)
	{
		movement *= input.GetDT() * currentSpeed;
		if (movement.x != 0 && movement.y != 0)
			movement *= 0.7071;

		TryMove(world, movement);
	}
}

void Player::Powerup()
{
	Heal(10);
	aoeAttack.currentCooldown = 0;
	aoeAttack.maxCount += 1;
	
	autoAttack.cooldown *= 0.9;
}