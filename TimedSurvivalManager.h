#pragma once
#include "World.h"
#include "InputHandler.h"
#include "Camera.h"
#include "EnemyFactory.h"

class TimedSurvivalManager
{
	World* world{};
	EnemyFactory factory;
	float duration{};
	unsigned int score{};
	float nextSpawn{};
	float nextPowerup{};
	float timer{};

public:
	TimedSurvivalManager();

	void Setup(World* _world, unsigned int _duration);

	bool RunTick(InputHandler& input, Camera& camera);

	unsigned int GetScore();
};