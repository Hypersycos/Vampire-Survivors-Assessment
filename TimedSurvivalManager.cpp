#include "TimedSurvivalManager.h"
#include "Runner.h"

TimedSurvivalManager::TimedSurvivalManager()
{
}

void TimedSurvivalManager::Setup(World* _world, unsigned int _duration)
{
	score = 0;
	timer = 0;
	duration = _duration;
	world = _world;
	nextSpawn = 1;
	nextPowerup = 10;
}

unsigned int TimedSurvivalManager::GetScore()
{
	return score;
}

static Vector<float> GetOffscreenPos(Camera& camera, World* world, Sprite* sprite)
{
	Vector<float> topLeft = camera.GetCameraTopLeft();
	Vector<int> cameraSize = (Vector<int>)camera.GetCameraViewSize();

	Vector<int> pos;

	Vector<int> spriteSize = sprite->GetSize().Ceil<int>();

	const int xVariance = cameraSize.x / 2 - spriteSize.x;
	const int yVariance = cameraSize.y / 2 - spriteSize.y;

	bool valid = false;

	while (!valid)
	{
		int edge = rand() % 4;

		switch (edge)
		{
		case 0:
			pos = { rand() % (cameraSize.x * 2) - cameraSize.x / 2, -rand() % yVariance - spriteSize.y };
			break;
		case 1:
			pos = { rand() % xVariance + spriteSize.x + cameraSize.x , rand() % (cameraSize.y * 2) - cameraSize.y / 2 };
			break;
		case 2:
			pos = { rand() % (cameraSize.x * 2) - cameraSize.x / 2, rand() % yVariance + cameraSize.y + spriteSize.y };
			break;
		case 3:
			pos = { -rand() % xVariance - spriteSize.x, rand() % (cameraSize.y * 2) - cameraSize.y / 2 };
			break;
		}
		pos += topLeft;

		valid = true;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (world->TileAt(pos + Vector<float>(spriteSize.x * i, spriteSize.y * j)) == nullptr)
				{
					valid = false;
					break;
				}
			}
		}
	}

	return pos;
}

#include <iostream>

bool TimedSurvivalManager::RunTick(InputHandler& input, Camera& camera)
{
	//if (timer > duration)
	//	return true;
	//if (world->GetPlayer()->GetHealth() <= 0)
	//	return true;

	world->Update(input);

	DynamicArray<Enemy*>& enemies = world->GetEnemies();
	for (unsigned int i = 0; i < enemies.GetCurrentSize(); i++)
	{
		Enemy* e = enemies[i];
		if (e != nullptr && e->GetHealth() <= 0)
		{
			score += 10;
			world->DespawnEnemy(i--, e);
			delete e;
		}

	}

	timer += input.GetDT();

	if (timer > nextPowerup)
	{
		Powerup* p = new Powerup();
		p->SetTopLeftPosition(GetOffscreenPos(camera, world, p));
		world->SpawnPowerup(p);
		nextPowerup += (rand() % 1000) / 100.0f + 5;
	}

	if (timer > nextSpawn)
	{
		float cost;
		Enemy* enemy = factory.SpawnEnemy(&cost);

		enemy->SetTopLeftPosition(GetOffscreenPos(camera, world, enemy));

		world->SpawnEnemy(enemy);

		nextSpawn += (1.2f - (timer / duration)) * cost;
	}

	return false;
}
