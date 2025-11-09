#pragma once

#include "Character.h"
#include "EnemyImageHolder.h"

class Enemy : public Character
{
protected:
	Vector<float> Pathfind(World* world, float dt);
	float flashTime{ 0 };

public:

	enum Enemies : char
	{
		Basic = 0,
		Artillery = 1,
		Runner = 2,
		MineLayer = 3,
	};

	virtual Enemies GetType() = 0;

	inline static EnemyImageHolder ImageHolder;

	Enemy(unsigned int maxHP, float baseSpeed, ImageSet img, Vector<float> position, Vector<float> collisionBox, CollisionLayer layer = CollidesWithPlayerProjectiles);
	Enemy(unsigned int maxHP, float baseSpeed, ImageSet img, Vector<float> collisionBox, CollisionLayer layer = CollidesWithPlayerProjectiles);

	void Update(World* world, InputHandler& input) override;

	bool Damage(int amount) override;

	void Serialize(std::ostream& stream) override;
};