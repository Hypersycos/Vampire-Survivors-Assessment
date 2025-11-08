#pragma once
#include "Enemy.h"

class Runner : public Enemy
{
	enum CharacterState
	{
		Chasing,
		Turning,
		Recovering
	};

	float timer;
	CharacterState state;
	Vector<float> direction;

	void Update(World* world, InputHandler& input) override;

public:
	Runner(Vector<float> position);
	Runner();

	void Serialize(std::ostream& stream) override;
	void Deserialize(std::istream& stream) override;

	// Inherited via Enemy
	Enemies GetType() override;
};