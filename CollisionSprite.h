#pragma once
#include "Sprite.h"

class CollisionSprite : public Sprite
{
public:
	enum CollisionLayer
	{
		Unset = -1,
		CollidesWithPlayer = 0,
		CollidesWithEnemies = 1,
		CollidesWithPlayerProjectiles = 2,
		CollidesWithEnemyProjectiles = 3
	};


private:
	Vector<float> collisionBox;
	CollisionLayer layer;

public:
	CollisionSprite();

	CollisionSprite(ImageSet img, Vector<float> collisionBox, CollisionLayer layer);

	CollisionSprite(ImageSet img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer);

	bool checkCollision(CollisionSprite* other);
	CollisionLayer getLayer() const;

	Vector<float> GetCollisionSize() const;
};