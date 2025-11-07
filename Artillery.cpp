#include "Artillery.h"
#include "World.h"
#include "Projectile.h"

#define maxHP 15
#define baseSpeed 60
#define collisionBox Vector<float>{ 30, 30 }

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
			state = Transforming;
		}
		break;
	case Artillery::Transforming:
		if ((timer += input.GetDT()) >= transformTime)
		{
			timer = fireInterval;
			state = Firing;
		}
		break;
	case Artillery::Firing:
		if ((timer += input.GetDT()) >= fireInterval)
		{
			timer -= fireInterval;
			//TODO: fire projectile
			Projectile* p = new Projectile(damage, (world->GetPlayer()->GetPosition() - position).scaleTo(projectileSpeed), position, &Tile::GetTile(3)->image, Vector<float>(20, 20), CollidesWithPlayer, 10);
			world->SpawnProjectile(p);
		}
		if ((world->GetPlayer()->GetPosition() - position).sqrMagnitude() > detransformDist * detransformDist)
		{
			timer = 0;
			state = Detransforming;
		}
		break;
	case Artillery::Detransforming:
		if ((timer += input.GetDT()) >= detransformTime)
		{
			state = Chasing;
		}
		break;
	default:
		break;
	}
}

Artillery::Artillery(Vector<float> position) : Enemy(maxHP, baseSpeed, Enemy::ImageHolder.GetImage(0), position, collisionBox), state(Chasing), timer(0)
{
	SetScale(0.5);
}

Artillery::Artillery() : Enemy(maxHP, baseSpeed, Enemy::ImageHolder.GetImage(0), collisionBox), state(Chasing), timer(0)
{
	SetScale(0.5);
}

