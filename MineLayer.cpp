#include "MineLayer.h"
#include "World.h"
#include "EnemyMine.h"

#define maxHP 25
#define baseSpeed 100
#define collisionBox Vector<float>{ 60, 60 }

#define mineDamage 10
#define mineInterval 2
#define mineTime 1
#define minesDropped 4
#define mineSpeed 20

void MineLayer::Update(World* world, InputHandler& input)
{
	Enemy::Update(world, input);
	switch (state)
	{
	case MineLayer::Chasing:
		TryMove(world, Pathfind(world, input.GetDT()));
		if ((timer += input.GetDT()) >= mineInterval)
		{
			timer = 0;
			state = Mining;
		}
		break;
	case MineLayer::Mining:
		if ((timer += input.GetDT()) >= mineTime)
		{
			timer = 0;
			state = Chasing;
			for (int i = 0; i < minesDropped; i++)
			{
				int direction = (rand() % 360) * 3.14159 / 180;
				Projectile* p = new EnemyMine(mineDamage, Vector<float>{(float)std::cos(direction), (float)std::sin(direction)}.scaleTo(20), position, 20, 2);
				world->SpawnProjectile(p);
			}
		}
		break;
	default:
		break;
	}
}

MineLayer::MineLayer(Vector<float> position) : Enemy(maxHP, baseSpeed, {Enemy::ImageHolder.GetImage(3)}, position, collisionBox), state(Chasing), timer(0)
{
	SetScale(0.75);
}

MineLayer::MineLayer() : Enemy(maxHP, baseSpeed, {Enemy::ImageHolder.GetImage(3)}, collisionBox), state(Chasing), timer(0)
{
	SetScale(0.75);
}

void MineLayer::Deserialize(std::istream& stream)
{
	Enemy::Deserialize(stream);
	stream.read(reinterpret_cast<char*>(&timer), sizeof(timer));
	stream.read(reinterpret_cast<char*>(&state), sizeof(state));
}

Enemy::Enemies MineLayer::GetType()
{
	return Enemy::MineLayer;
}

void MineLayer::Serialize(std::ostream& stream)
{
	Enemy::Serialize(stream);
	stream.write(reinterpret_cast<char*>(&timer), sizeof(timer));
	stream.write(reinterpret_cast<char*>(&state), sizeof(state));
}

