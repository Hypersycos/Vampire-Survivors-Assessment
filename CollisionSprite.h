#pragma once
#include "Sprite.h"

class CollisionSprite : public Sprite
{
	float collisionRadius;
	Vector<float> lastPos;
	CollisionLayer layer;

public:
	CollisionSprite();

	CollisionSprite(std::istream& stream);

	CollisionSprite(GamesEngineeringBase::Image* img, float collisionRadius, CollisionLayer layer);

	CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer);

	bool checkCollision(CollisionSprite* other);
	CollisionLayer getLayer() const;

	float GetRadius() const;

	void Update(World* world, InputHandler& input) override;
};