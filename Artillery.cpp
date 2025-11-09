#include "Artillery.h"
#include "World.h"
#include "EnemyProjectile.h"

#define maxHP 15
#define baseSpeed 60
#define collisionBox Vector<float>{ 80, 80 }

#define transformDist 320
#define transformTime 1
#define detransformDist 380
#define detransformTime 1
#define damage 10
#define fireInterval 2
#define projectileSpeed 360

void Artillery::Update(World* world, InputHandler& input)
{
	switch (state)
	{
	case Artillery::Chasing:
		TryMove(world, Pathfind(world, input.GetDT()));
		if ((world->GetPlayer()->GetPosition() - position).sqrMagnitude() < transformDist * transformDist)
		{
			timer = 0;
			SetState(Transforming);
		}
		break;
	case Artillery::Transforming:
		if ((timer += input.GetDT()) >= transformTime)
		{
			timer = fireInterval;
			SetState(Firing);
		}
		break;
	case Artillery::Firing:
		if ((timer += input.GetDT()) >= fireInterval)
		{
			timer -= fireInterval;
			Projectile* p = new EnemyProjectile(damage, (world->GetPlayer()->GetPosition() - position).scaleTo(projectileSpeed), position, 5);
			world->SpawnProjectile(p);
		}
		if ((world->GetPlayer()->GetPosition() - position).sqrMagnitude() > detransformDist * detransformDist)
		{
			timer = 0;
			SetState(Detransforming);
		}
		break;
	case Artillery::Detransforming:
		if ((timer += input.GetDT()) >= detransformTime)
		{
			SetState(Chasing);
		}
		break;
	default:
		break;
	}
}

void Artillery::SetState(CharacterState newState)
{
	switch (newState)
	{
	case Artillery::Transforming:
	case Artillery::Detransforming:
		SetImage(Enemy::ImageHolder.GetImage(5));
		break;
	case Artillery::Firing:
		SetImage(Enemy::ImageHolder.GetImage(0));
		break;
	case Artillery::Chasing:
		SetImage(Enemy::ImageHolder.GetImage(4));
		break;
	default:
		return;
	}
	state = newState;
}

Artillery::Artillery(Vector<float> position) : Enemy(maxHP, baseSpeed, Enemy::ImageHolder.GetImage(4), position, collisionBox), state(Chasing), timer(0)
{
}

Artillery::Artillery() : Enemy(maxHP, baseSpeed, Enemy::ImageHolder.GetImage(4), collisionBox), state(Chasing), timer(0)
{
}

void Artillery::Deserialize(std::istream& stream)
{
	Enemy::Deserialize(stream);
	stream.read(reinterpret_cast<char*>(&timer), sizeof(timer));
	stream.read(reinterpret_cast<char*>(&state), sizeof(state));
}

Enemy::Enemies Artillery::GetType()
{
	return Enemy::Artillery;
}

void Artillery::Serialize(std::ostream& stream)
{
	Enemy::Serialize(stream);
	stream.write(reinterpret_cast<char*>(&timer), sizeof(timer));
	stream.write(reinterpret_cast<char*>(&state), sizeof(state));
	SetState(state);
}

