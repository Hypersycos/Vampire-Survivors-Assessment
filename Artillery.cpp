#include "Artillery.h"
#include "World.h"
#include "Projectile.h"

void Artillery::Update(World* world, InputHandler& input)
{
	switch (state)
	{
	case Artillery::Chasing:
		Move(Pathfind(world, input.GetDT()));
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
			Projectile* p = new Projectile(damage, (world->GetPlayer()->GetPosition() - position).scaleTo(projectileSpeed), position, world->GetTileImage(3), 20, CollidesWithPlayer);
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

Artillery::Artillery(Vector<float> position) : Enemy(maxHP, baseSpeed, Enemy::ImageHolder.GetImage(0), position, collisionRadius), state(Chasing), timer(0)
{
	SetScale(0.5);
}
