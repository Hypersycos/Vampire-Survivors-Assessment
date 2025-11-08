#include "PlayerProjectile.h"
#include "Tile.h"

PlayerProjectile::PlayerProjectile(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime) : Projectile(damage, movement, position, &Tile::GetTile(2)->image, Vector<float>(16, 16), CollidesWithEnemies, lifetime)
{
	SetScale(0.5);
}

PlayerProjectile::PlayerProjectile(std::istream& stream) : Projectile(0, Vector<float>(), Vector<float>(), &Tile::GetTile(2)->image, Vector<float>(16, 16), CollidesWithEnemies, 0)
{
	Deserialize(stream);
}
