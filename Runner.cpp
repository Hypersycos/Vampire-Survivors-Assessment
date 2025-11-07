#include "Runner.h"
#include "World.h"

#define maxHP 25
#define startingSpeed 30
#define acceleration 75
#define collisionBox Vector<float>{ 30, 30 }

#define damagePer10 1
#define turningRecovery 1
#define attackRecovery 1

void Runner::Update(World* world, InputHandler& input)
{
	switch (state)
	{
	case Chasing:
	{
		Vector<float> TargetDir = Pathfind(world, input.GetDT()).scaleTo(1);

		float turnRate = startingSpeed / baseSpeed;
		direction = direction * (1 - turnRate) + TargetDir * turnRate;

		float dot = TargetDir.Dot<float>(direction);

		baseSpeed = baseSpeed * dot;
		baseSpeed += input.GetDT() * acceleration;

		if (baseSpeed < startingSpeed + acceleration)
		{
			timer = 0;
			state = Turning;
		}

		TryMove(world, TargetDir * currentSpeed * input.GetDT());

		if (checkCollision(world->GetPlayer()))
		{
			timer = 0;
			state = Recovering;
			world->GetPlayer()->Damage(currentSpeed / 10 * damagePer10);
		}
		break;
	}
	case Turning:
		if ((timer += input.GetDT()) > turningRecovery)
		{
			direction = Pathfind(world, 1).scaleTo(1);
			baseSpeed = startingSpeed + acceleration * turningRecovery * 2;
			state = Chasing;
		}
		break;
	case Recovering:
		if ((timer += input.GetDT()) > attackRecovery)
			state = Turning;
		break;
	}
}

Runner::Runner(Vector<float> position) : Enemy(maxHP, startingSpeed, Enemy::ImageHolder.GetImage(1), position, collisionBox), state(Turning), timer(turningRecovery)
{
	SetScale(0.5);
}

Runner::Runner() : Enemy(maxHP, startingSpeed, Enemy::ImageHolder.GetImage(1), collisionBox), state(Turning), timer(turningRecovery)
{
	SetScale(0.5);
}

