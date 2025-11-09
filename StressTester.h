#pragma once
#include "World.h"
#include "InputHandler.h"
#include "Camera.h"
#include "FollowCamera.h"
#include "EnemyFactory.h"

class StressTester
{
	World* world{};
	EnemyFactory factory;
	
	unsigned int currentCount;
	unsigned int intendedCount;

	Camera camera;
	FollowCamera target;
	Canvas& canvas;

public:
	StressTester(Canvas& canvas);

	void Setup(World* _world);

	void Load(std::string path);

	void Save(std::string path);

	bool RunTick(InputHandler& input);

	void Draw(InputHandler& input);

	void DrawBar(float threshold, int width, int height, Vector<int> position, unsigned char* color1, unsigned char* color2, unsigned char& alpha, Canvas& canvas);
};