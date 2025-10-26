#pragma once
#include "Sprite.h"

class CollisionSprite : Sprite
{
	float collisionRadius;
	int layer;

public:
	CollisionSprite();

	CollisionSprite(GamesEngineeringBase::Image* img, float collisionRadius, int layer);

	CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, int layer);

	bool checkCollision(CollisionSprite& other);
	int getLayer() const;
};