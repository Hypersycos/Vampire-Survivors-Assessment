#include "EnemyProjectile.h"
#include "Tile.h"

EnemyProjectile::EnemyProjectile(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime) : Projectile(damage, movement, position, &Tile::GetTile(3)->image, Vector<float>(16, 16), CollidesWithPlayer, lifetime)
{
	SetScale(0.5);
}

EnemyProjectile::EnemyProjectile(std::istream& stream) : Projectile(0, Vector<float>(), Vector<float>(), &Tile::GetTile(3)->image, Vector<float>(16, 16), CollidesWithPlayer, 0)
{
	Deserialize(stream);
}
