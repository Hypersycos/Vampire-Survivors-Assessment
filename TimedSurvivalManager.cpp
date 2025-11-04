#include "TimedSurvivalManager.h"
#include "Artillery.h"

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
}

unsigned int TimedSurvivalManager::GetScore()
{
	return score;
}

bool TimedSurvivalManager::RunTick(InputHandler& input, Camera& camera)
{
	if (timer > duration)
		return true;
	if (world->GetPlayer()->GetHealth() <= 0)
		return true;

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

	if (floor(timer) < floor(timer += input.GetDT()))
		score++;

	if (timer > nextSpawn)
	{
		Vector<float> topLeft = camera.GetCameraTopLeft();
		Vector<unsigned int> cameraSize = camera.GetCameraViewSize();

		int edge = rand() % 4;
		Vector<int> pos;

		switch (edge)
		{
		case 0:
			pos = {rand() % ((int)cameraSize.x + 200) - 100, rand() % 100 - 100 };
			break;
		case 1:
			pos = {rand() % 100 + (int)cameraSize.x , rand() % ((int)cameraSize.x + 200) - 100};
			break;
		case 2:
			pos = { rand() % ((int)cameraSize.x + 200) - 100, rand() % 100 + (int)cameraSize.y };
			break;
		case 3:
			pos = { rand() % 100 - 100 + (int)cameraSize.x , rand() % ((int)cameraSize.x + 200) - 100 };
			break;
		}

		world->SpawnEnemy(new Artillery(topLeft + pos));

		nextSpawn += (1.2f - (timer / duration)) * 1;
	}

	return false;
}
