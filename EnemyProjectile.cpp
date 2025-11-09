#include "EnemyProjectile.h"
#include "Tile.h"

EnemyProjectile::EnemyProjectile(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime) : Projectile(damage, movement, position, {GetImage()}, Vector<float>(12, 12), CollidesWithPlayer, lifetime)
{
	SetScale(0.15);
}

EnemyProjectile::EnemyProjectile(std::istream& stream) : Projectile(0, Vector<float>(), Vector<float>(), {GetImage()}, Vector<float>(12, 12), CollidesWithPlayer, 0)
{
	Deserialize(stream);
}

void EnemyProjectile::Serialize(std::ostream& stream)
{
	char temp = 0;
	stream.write(&temp, 1);
	Projectile::Serialize(stream);
}

GamesEngineeringBase::Image* EnemyProjectile::GetImage()
{
	if (!imageLoaded)
	{
		enemyProjectileImage.load("Resources/pink_body_circle.png");
		imageLoaded = true;
	}
	return &enemyProjectileImage;
}