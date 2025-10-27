#include "CollisionSprite.h"

CollisionSprite::CollisionSprite() : Sprite(), collisionRadius(0), layer(-1)
{

}

CollisionSprite::CollisionSprite(GamesEngineeringBase::Image* img, float collisionRadius, int layer) : Sprite(img), collisionRadius(collisionRadius), layer(layer)
{
}

CollisionSprite::CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, int layer) : Sprite(img, position), collisionRadius(collisionRadius), layer(layer)
{
}

bool CollisionSprite::checkCollision(CollisionSprite& other)
{
	double distance = (other.GetPosition() - GetPosition()).magnitude();
	return (distance <= collisionRadius + other.collisionRadius);
}

int CollisionSprite::getLayer() const
{
	return layer;
}
