#include "Player.h"
#include "Enemy.h"
#include "World.h"

static float GetEnemyHealth(Enemy* enemy)
{
	return (float)enemy->GetHealth();
}

Player::Player() : Character(100, 200, nullptr, Vector<float>(0, 0), 16, CollidesWithEnemyProjectiles)
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
		Projectile* p = new Projectile(autoAttack.damage, (nearest->GetPosition() - position).scaleTo(autoAttack.baseSpeed), position, world->GetTileImage(2), 20, CollidesWithEnemies);
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

		world->TryMove(this, movement);
	}
}