#include "Player.h"
#include "Enemy.h"
#include "World.h"

#include "PlayerProjectile.h"

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

AoEAttack::AoEAttack() : AoEAttack{ 4, 25, 256, 3 }
{
}

Player::Player() : Character(100, 200, { GetPlayerImage() }, Vector<float>(0, 0), Vector<float>(30, 30), CollidesWithEnemyProjectiles)
{
	enabled = true;
	SetScale(0.375f);
}

void Player::Serialize(std::ostream& stream)
{
	Character::Serialize(stream);
	stream.write(reinterpret_cast<char*>(&aoeAttack.currentCooldown), sizeof(aoeAttack.currentCooldown));
	stream.write(reinterpret_cast<char*>(&autoAttack.currentCooldown), sizeof(autoAttack.currentCooldown));
	stream.write(reinterpret_cast<char*>(&autoAttack.cooldown), sizeof(autoAttack.cooldown));
	stream.write(reinterpret_cast<char*>(&aoeAttack.maxCount), sizeof(aoeAttack.maxCount));
}

void Player::Deserialize(std::istream& stream)
{
	Character::Deserialize(stream);
	stream.read(reinterpret_cast<char*>(&aoeAttack.currentCooldown), sizeof(aoeAttack.currentCooldown));
	stream.read(reinterpret_cast<char*>(&autoAttack.currentCooldown), sizeof(autoAttack.currentCooldown));
	stream.read(reinterpret_cast<char*>(&autoAttack.cooldown), sizeof(autoAttack.cooldown));
	stream.read(reinterpret_cast<char*>(&aoeAttack.maxCount), sizeof(aoeAttack.maxCount));
}

GamesEngineeringBase::Image* Player::GetPlayerImage()
{
	if (!imageLoaded)
	{
		playerImage.load("Resources/yellow_body_square.png");
		imageLoaded = true;
	}
	return &playerImage;
}

static float GetEnemyHealth(Enemy* enemy)
{
	return -(float)enemy->GetHealth();
}

void Player::Update(World* world, InputHandler& input)
{
	CollisionSprite::Update(world, input);
	bool doAoE = aoeAttack.ApplyCooldown(input.GetDT(), input.KeyDown(' '));

	Enemy* nearest = world->GetNearestEnemyToPlayer(autoAttack.range);
	bool doAttack = autoAttack.ApplyCooldown(input.GetDT(), nearest != nullptr);

	while (doAttack)
	{ //allows multiple fires if both FPS and attack cooldown are very low
		Projectile* p = new PlayerProjectile(autoAttack.damage, (nearest->GetPosition() - position).scaleTo(autoAttack.baseSpeed), position, 5);
		world->SpawnProjectile(p);
		doAttack = autoAttack.ApplyCooldown(input.GetDT(), nearest != nullptr);
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
		//prevent diagonal movement being faster
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

float Player::GetAoeCooldownPercent()
{
	return aoeAttack.currentCooldown / aoeAttack.cooldown;
}
