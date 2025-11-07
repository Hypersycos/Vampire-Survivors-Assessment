#include "Powerup.h"
#include "World.h"

Powerup::Powerup(Vector<float> position) : CollisionSprite(Enemy::ImageHolder.GetImage(0), Vector<float>(32, 32), CollidesWithPlayer)
{
}

Powerup::Powerup() : Powerup(Vector<float>(0, 0))
{
}
