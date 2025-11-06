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

	if (false && timer > nextSpawn)
	{
		Vector<float> topLeft = camera.GetCameraTopLeft();
		Vector<int> cameraSize = (Vector<int>)camera.GetCameraViewSize();

		Enemy* enemy = new Artillery();

		Vector<int> pos;

		Vector<int> spriteSize = enemy->GetSize().Ceil<int>();

		const int xVariance = cameraSize.x / 2 - spriteSize.x;
		const int yVariance = cameraSize.y / 2 - spriteSize.y;

		do
		{
			int edge = rand() % 4;

			switch (edge)
			{
			case 0:
				pos = { rand() % (cameraSize.x * 2) - cameraSize.x / 2, - rand() % yVariance - spriteSize.y};
				break;
			case 1:
				pos = { rand() % xVariance + spriteSize.x + cameraSize.x , rand() % (cameraSize.y * 2) - cameraSize.y / 2 };
				break;
			case 2:
				pos = { rand() % (cameraSize.x * 2) - cameraSize.x / 2, rand() % yVariance + cameraSize.y + spriteSize.y };
				break;
			case 3:
				pos = { - rand() % xVariance - spriteSize.x, rand() % (cameraSize.y * 2) - cameraSize.y / 2 };
				break;
			}
			pos += topLeft;
		} while (world->TileAt(pos) == -1);

		enemy->SetTopLeftPosition(pos);

		world->SpawnEnemy(enemy);

		nextSpawn += (1.2f - (timer / duration)) * 1;
	}

	return false;
}
