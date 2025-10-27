#include "CollisionSprite.h"

class Projectile : CollisionSprite
{
	int damage;
	Vector<float> movement;

	void Update(World* world, InputHandler& input)
	{
		Move(movement);
	}
};