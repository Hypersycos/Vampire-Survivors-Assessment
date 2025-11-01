#include "Artillery.h"
#include "World.h"

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
		if (timer += input.GetDT() >= transformTime)
		{
			timer = fireInterval;
			state = Firing;
		}
		break;
	case Artillery::Firing:
		if (timer += input.GetDT() >= fireInterval)
		{
			timer -= fireInterval;
			//fire projectile
		}
		if ((world->GetPlayer()->GetPosition() - position).sqrMagnitude() > detransformDist * detransformDist)
		{
			timer = 0;
			state = Detransforming;
		}
		break;
	case Artillery::Detransforming:
		if (timer += input.GetDT() >= transformTime)
		{
			state = Chasing;
		}
		break;
	default:
		break;
	}
}

Artillery::Artillery(Vector<float> position) : Enemy(maxHP, baseSpeed, nullptr, position, collisionRadius), state(Chasing), timer(0)
{
}
