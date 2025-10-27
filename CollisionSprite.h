#pragma once
#include "Sprite.h"

class CollisionSprite : public Sprite
{
	float collisionRadius;
	Vector<float> lastPos;
	CollisionLayer layer;

public:
	CollisionSprite();

	CollisionSprite(GamesEngineeringBase::Image* img, float collisionRadius, CollisionLayer layer);

	CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer);

	bool checkCollision(CollisionSprite& other);
	int getLayer() const;

	void Update(World* world, InputHandler& input) override;
};