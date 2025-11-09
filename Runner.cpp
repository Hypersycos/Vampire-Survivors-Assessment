#include "Runner.h"
#include "World.h"

#define maxHP 25
#define startingSpeed 30
#define acceleration 75
#define collisionBox Vector<float>{ 40, 40 }

#define damagePer10 0.5
#define turningRecovery 1
#define attackRecovery 1

void Runner::Update(World* world, InputHandler& input)
{
	switch (state)
	{
	case Chasing:
	{
		Vector<float> TargetDir = Pathfind(world, input.GetDT()).scaleTo(1);

		float turnRate = startingSpeed / (baseSpeed * baseSpeed / 50);
		direction = direction * (1 - turnRate) + TargetDir * turnRate;

		float dot = TargetDir.Dot<float>(direction);

		baseSpeed += input.GetDT() * dot * acceleration;

		if (dot < -0.5)
		{
			timer = 0;
			state = Turning;
		}

		TryMove(world, direction * currentSpeed * input.GetDT());

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

Runner::Runner(Vector<float> position) : Enemy(maxHP, startingSpeed, Enemy::ImageHolder.GetImage(2), position, collisionBox), state(Turning), timer(turningRecovery)
{
	SetScale(0.5);
}

Runner::Runner() : Enemy(maxHP, startingSpeed, Enemy::ImageHolder.GetImage(2), collisionBox), state(Turning), timer(turningRecovery)
{
	SetScale(0.5);
}

void Runner::Deserialize(std::istream& stream)
{
	Enemy::Deserialize(stream);
	stream.read(reinterpret_cast<char*>(&timer), sizeof(timer));
	stream.read(reinterpret_cast<char*>(&state), sizeof(state));
	stream.read(reinterpret_cast<char*>(&baseSpeed), sizeof(baseSpeed));
	stream.read(reinterpret_cast<char*>(&direction), sizeof(direction));
}

Enemy::Enemies Runner::GetType()
{
	return Enemy::Runner;
}

void Runner::Serialize(std::ostream& stream)
{
	Enemy::Serialize(stream);
	stream.write(reinterpret_cast<char*>(&timer), sizeof(timer));
	stream.write(reinterpret_cast<char*>(&state), sizeof(state));
	stream.write(reinterpret_cast<char*>(&baseSpeed), sizeof(baseSpeed));
	stream.write(reinterpret_cast<char*>(&direction), sizeof(direction));
}