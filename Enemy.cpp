#include "Enemy.h"
#include "World.h"
#pragma once

Enemy::Enemy(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer) : Character(maxHP, baseSpeed, img, position, collisionBox, layer)
{
}

Enemy::Enemy(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> collisionBox, CollisionLayer layer) : Character(maxHP, baseSpeed, img, collisionBox, layer)
{
}

void Enemy::Update(World* world, InputHandler& input)
{
	Move(Pathfind(world, input.GetDT()));
}

Vector<float> Enemy::Pathfind(World* world, float dt)
{
	return (world->GetPlayer()->GetPosition() - position).clamped(currentSpeed * dt);
}
