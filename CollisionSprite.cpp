#include "CollisionSprite.h"

CollisionSprite::CollisionSprite() : Sprite(), collisionBox(Vector<float>{}), layer(Unset)
{

}

CollisionSprite::CollisionSprite(ImageSet img, Vector<float> collisionBox, CollisionLayer layer) : Sprite(img), collisionBox(collisionBox), layer(layer)
{
}

CollisionSprite::CollisionSprite(ImageSet img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer) : Sprite(img, position), collisionBox(collisionBox), layer(layer)
{
}

bool CollisionSprite::checkCollision(CollisionSprite* other)
{ //intersection of two squares
	Vector<float> distance = (other->GetPosition() - GetPosition()).Abs();
	return distance.x < (other->collisionBox.x + collisionBox.x) / 2 && distance.y < (other->collisionBox.y + collisionBox.y) / 2;
}

CollisionSprite::CollisionLayer CollisionSprite::getLayer() const
{
	return layer;
}

Vector<float> CollisionSprite::GetCollisionSize() const
{
	return collisionBox;
}