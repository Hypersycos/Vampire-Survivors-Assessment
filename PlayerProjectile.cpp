#include "PlayerProjectile.h"
#include "Tile.h"

PlayerProjectile::PlayerProjectile(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime) : Projectile(damage, movement, position, GetImage(), Vector<float>(20, 20), CollidesWithEnemies, lifetime)
{
	SetScale(0.15);
}

PlayerProjectile::PlayerProjectile(std::istream& stream) : Projectile(0, Vector<float>(), Vector<float>(), GetImage(), Vector<float>(20, 20), CollidesWithEnemies, 0)
{
	Deserialize(stream);
}

GamesEngineeringBase::Image* PlayerProjectile::GetImage()
{
	if (!imageLoaded)
	{
		playerProjectileImage.load("Resources/yellow_body_circle.png");
		imageLoaded = true;
	}
	return &playerProjectileImage;
}