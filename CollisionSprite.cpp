#include "CollisionSprite.h"

CollisionSprite::CollisionSprite() : Sprite(), collisionBox(Vector<float>{}), layer(Unset)
{

}

CollisionSprite::CollisionSprite(std::istream& stream) : Sprite(stream), layer(Unset)
{
}

CollisionSprite::CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> collisionBox, CollisionLayer layer) : Sprite(img), collisionBox(collisionBox), layer(layer)
{
}

CollisionSprite::CollisionSprite(GamesEngineeringBase::Image* img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer) : Sprite(img, position), collisionBox(collisionBox), layer(layer)
{
}

#include <iostream>

bool CollisionSprite::checkCollision(CollisionSprite* other)
{
	Vector<float> distance = (other->GetPosition() - GetPosition()).Abs();
	return distance.x < (other->collisionBox.x + collisionBox.x) / 2 && distance.y < (other->collisionBox.y + collisionBox.y) / 2;
}

CollisionLayer CollisionSprite::getLayer() const
{
	return layer;
}

Vector<float> CollisionSprite::GetCollisionSize() const
{
	return collisionBox;
}

void CollisionSprite::Update(World* world, InputHandler& input)
{
	lastPos = position;
}