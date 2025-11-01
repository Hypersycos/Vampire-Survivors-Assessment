#include "Enemy.h"
#include "World.h"
#pragma once

Enemy::Enemy(unsigned int maxHP, float baseSpeed, GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer = CollidesWithPlayerProjectiles) : Character(maxHP, baseSpeed, img, position, collisionRadius, layer)
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
