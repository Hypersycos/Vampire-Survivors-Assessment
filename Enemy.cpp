#include "Enemy.h"
#include "World.h"
#pragma once

Enemy::Enemy(unsigned int maxHP, float baseSpeed, ImageSet img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer) : Character(maxHP, baseSpeed, img, position, collisionBox, layer)
{
}

Enemy::Enemy(unsigned int maxHP, float baseSpeed, ImageSet img, Vector<float> collisionBox, CollisionLayer layer) : Character(maxHP, baseSpeed, img, collisionBox, layer)
{
}

void Enemy::Update(World* world, InputHandler& input)
{
	Move(Pathfind(world, input.GetDT()));
}

void Enemy::Serialize(std::ostream& stream)
{
	Enemy::Enemies type = GetType();
	stream.write(reinterpret_cast<char*>(&type), sizeof(type));
	Character::Serialize(stream);
}

Vector<float> Enemy::Pathfind(World* world, float dt)
{ //shortest path (straight line)
	return (world->GetPlayer()->GetPosition() - position).clamped(currentSpeed * dt);
}
