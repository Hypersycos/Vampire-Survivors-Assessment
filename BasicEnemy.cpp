#include "BasicEnemy.h"
#include "World.h"

#define maxHP 1
#define baseSpeed 160
#define collisionBox Vector<float>{ 30, 30 }

#define damage 4
#define attackInterval 1

void BasicEnemy::Update(World* world, InputHandler& input)
{
	switch (state)
	{
	case Chasing:
		TryMove(world, Pathfind(world, input.GetDT()));
		if (checkCollision(world->GetPlayer()))
		{
			timer = 0;
			state = Swiping;
			world->GetPlayer()->Damage(damage);
		}
		break;
	case Swiping:
		if ((timer += input.GetDT()) > attackInterval)
			state = Chasing;
		break;
	}
}

BasicEnemy::BasicEnemy(Vector<float> position) : Enemy(maxHP, baseSpeed, Enemy::ImageHolder.GetImage(1), position, collisionBox), state(Chasing), timer(0)
{
	SetScale(0.5);
}

BasicEnemy::BasicEnemy() : Enemy(maxHP, baseSpeed, Enemy::ImageHolder.GetImage(1), collisionBox), state(Chasing), timer(0)
{
	SetScale(0.5);
}

