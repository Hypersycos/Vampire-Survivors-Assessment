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

	void SetState(CharacterState newState);

public:
	Artillery(Vector<float> position);
	Artillery();

	void Serialize(std::ostream& stream) override;
	void Deserialize(std::istream& stream) override;

	// Inherited via Enemy
	Enemies GetType() override;
};