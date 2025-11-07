#pragma once
#include "Sprite.h"

class CollisionSprite : public Sprite
{
	Vector<float> collisionBox;
	Vector<float> lastPos;
	CollisionLayer layer;

public:
	CollisionSprite();

	CollisionSprite(std::istream& stream);

	CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> collisionBox, CollisionLayer layer);

	CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer);

	bool checkCollision(CollisionSprite* other);
	CollisionLayer getLayer() const;

	Vector<float> GetCollisionSize() const;

	void Update(World* world, InputHandler& input) override;
};