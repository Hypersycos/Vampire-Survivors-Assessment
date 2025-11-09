#pragma once
#include "Enemy.h"

class MineLayer : public Enemy
{
	enum CharacterState
	{
		Chasing,
		Mining
	};

	float timer;
	CharacterState state;
	float contactDebounce;

	void Update(World* world, InputHandler& input) override;

public:
	MineLayer(Vector<float> position);
	MineLayer();

	void Serialize(std::ostream& stream) override;
	void Deserialize(std::istream& stream) override;

	// Inherited via Enemy
	Enemies GetType() override;
};