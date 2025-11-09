#include "BasicEnemy.h"
#include "World.h"

#define maxHP 1
#define baseSpeed 160
#define collisionBox Vector<float>{ 20, 20 }

#define damage 4
#define attackInterval 1

void BasicEnemy::Update(World* world, InputHandler& input)
{
	switch (state)
	{
	case Chasing:
		Move(Pathfind(world, input.GetDT()));
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
	SetScale(0.25);
}

BasicEnemy::BasicEnemy() : Enemy(maxHP, baseSpeed, Enemy::ImageHolder.GetImage(1), collisionBox), state(Chasing), timer(0)
{
	SetScale(0.25);
}

void BasicEnemy::Deserialize(std::istream& stream)
{
	Enemy::Deserialize(stream);
	stream.read(reinterpret_cast<char*>(&timer), sizeof(timer));
	stream.read(reinterpret_cast<char*>(&state), sizeof(state));
}

Enemy::Enemies BasicEnemy::GetType()
{
	return Enemy::Basic;
}

void BasicEnemy::Serialize(std::ostream& stream)
{
	Enemy::Serialize(stream);
	stream.write(reinterpret_cast<char*>(&timer), sizeof(timer));
	stream.write(reinterpret_cast<char*>(&state), sizeof(state));
}