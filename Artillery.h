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

	float timer;
	CharacterState state;

	void Update(World* world, InputHandler& input) override;

public:
	Artillery(Vector<float> position);
	Artillery();
};