#include "Powerup.h"
#include "World.h"

Powerup::Powerup(Vector<float> position) : CollisionSprite({ GetImage() }, Vector<float>(70, 68), CollidesWithPlayer)
{
}

Powerup::Powerup() : Powerup(Vector<float>(0, 0))
{
}

GamesEngineeringBase::Image* Powerup::GetImage()
{
	if (!imageLoaded)
	{
		powerupImage.load("Resources/hand_yellow_closed.png");
		imageLoaded = true;
	}
	return &powerupImage;
}