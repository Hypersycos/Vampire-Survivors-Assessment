#pragma once
#include "Enemy.h"

class Artillery : Enemy
{
	enum CharacterState
	{
		Chasing,
		Transforming,
		Firing,
		Detransforming
	};

	static unsigned int maxHP;
	static float baseSpeed;
	static float collisionRadius;
	static std::string spritePath;

	constexpr static float transformDist = 160;
	constexpr static float transformTime = 1;
	constexpr static float detransformDist = 300;
	constexpr static float detransformTime = 1;
	constexpr static float damage = 10;
	constexpr static float fireInterval = 2;

	float timer;
	CharacterState state;

	void Update(World* world, InputHandler& input) override;

	Artillery(Vector<float> position);
};