#pragma once
#include "Enemy.h"

class BasicEnemy : public Enemy
{
	enum CharacterState
	{
		Chasing,
		Swiping
	};

	float timer;
	CharacterState state;

	void Update(World* world, InputHandler& input) override;

public:
	BasicEnemy(Vector<float> position);
	BasicEnemy();
};