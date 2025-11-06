#include "CollisionSprite.h"

CollisionSprite::CollisionSprite() : Sprite(), collisionRadius(0), layer(Unset)
{

}

CollisionSprite::CollisionSprite(std::istream& stream) : Sprite(stream)
{
}

CollisionSprite::CollisionSprite(GamesEngineeringBase::Image* img, float collisionRadius, CollisionLayer layer) : Sprite(img), collisionRadius(collisionRadius), layer(layer)
{
}

CollisionSprite::CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> position, float collisionRadius, CollisionLayer layer) : Sprite(img, position), collisionRadius(collisionRadius), layer(layer)
{
}

bool CollisionSprite::checkCollision(CollisionSprite* other)
{
	double distance = (other->GetPosition() - GetPosition()).sqrMagnitude();
	double collRadius = (collisionRadius + other->collisionRadius) * (collisionRadius + other->collisionRadius);
	return (distance <= collRadius);
}

CollisionLayer CollisionSprite::getLayer() const
{
	return layer;
}

float CollisionSprite::GetRadius() const
{
	return collisionRadius;
}

void CollisionSprite::Update(World* world, InputHandler& input)
{
	lastPos = position;
}