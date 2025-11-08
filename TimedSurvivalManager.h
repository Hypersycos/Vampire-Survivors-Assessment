#pragma once
#include "World.h"
#include "InputHandler.h"
#include "Camera.h"
#include "FollowCamera.h"
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

	Camera camera;
	FollowCamera target;
	Canvas& canvas;

public:
	TimedSurvivalManager(Canvas& canvas);

	void Setup(World* _world, unsigned int _duration);

	void Load(std::string path);

	void Save(std::string path);

	bool RunTick(InputHandler& input);

	void Draw(InputHandler& input);

	unsigned int GetScore();
};