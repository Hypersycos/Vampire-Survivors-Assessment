#include "EnemyMine.h"
#include "Tile.h"

EnemyMine::EnemyMine(unsigned int damage, Vector<float> movement, Vector<float> position, float lifetime, float moveTime) : Projectile(damage, movement, position, GetImage(), Vector<float>(20, 20), CollidesWithPlayer, lifetime), movementTime(moveTime)
{
	SetScale(0.25);
}

EnemyMine::EnemyMine(std::istream& stream) : Projectile(0, Vector<float>(), Vector<float>(), GetImage(), Vector<float>(20, 20), CollidesWithPlayer, 0)
{
	Deserialize(stream);
}

void EnemyMine::Update(World* world, InputHandler& input)
{
	movementTime -= input.GetDT();
	if (movementTime <= 0 && (movement.x != 0 || movement.y != 0))
		movement = Vector<float>();
	Projectile::Update(world, input);
}

void EnemyMine::Serialize(std::ostream& stream)
{
	char temp = 1;
	stream.write(&temp, 1);
	Projectile::Serialize(stream);
	stream.write(reinterpret_cast<char*>(&movementTime), sizeof(movementTime));
}

void EnemyMine::Deserialize(std::istream& stream)
{
	Projectile::Deserialize(stream);
	stream.read(reinterpret_cast<char*>(&movementTime), sizeof(movementTime));
}

GamesEngineeringBase::Image* EnemyMine::GetImage()
{
	if (!imageLoaded)
	{
		enemyProjectileImage.load("Resources/red_body_square.png");
		imageLoaded = true;
	}
	return &enemyProjectileImage;
}