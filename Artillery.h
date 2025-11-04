#pragma once
#include "Enemy.h"

class Artillery : public Enemy
{
	enum CharacterState
	{
		Chasing,
		Transforming,
		Firing,
		Detransforming
	};

	inline static const unsigned int maxHP = 15;
	inline static const float baseSpeed = 60;
	inline static const float collisionRadius = 60;

	inline static const float transformDist = 320;
	inline static const float transformTime = 1;
	inline static const float detransformDist = 380;
	inline static const float detransformTime = 1;
	inline static const unsigned int damage = 10;
	inline static const float fireInterval = 2;
	inline static const float projectileSpeed = 12;

	float timer;
	CharacterState state;

	void Update(World* world, InputHandler& input) override;

public:
	Artillery(Vector<float> position);
};