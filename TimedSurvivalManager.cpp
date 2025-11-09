#include "TimedSurvivalManager.h"
#include "FixedWorld.h"
#include "InfiniteWorld.h"
#include "RepeatingFixedWorld.h"
#include "font.h"

TimedSurvivalManager::TimedSurvivalManager(Canvas& canvas) : canvas(canvas), camera{nullptr, canvas, &target}
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

	target.SetTarget(world->GetPlayer());
	camera.SetWorld(world);
}

void TimedSurvivalManager::Load(std::string path)
{
	std::ifstream worldState{ path, std::ios::binary };

	worldState.read(reinterpret_cast<char*>(&score), sizeof(score));
	worldState.read(reinterpret_cast<char*>(&timer), sizeof(timer));
	worldState.read(reinterpret_cast<char*>(&duration), sizeof(duration));
	worldState.read(reinterpret_cast<char*>(&nextSpawn), sizeof(nextSpawn));
	worldState.read(reinterpret_cast<char*>(&nextPowerup), sizeof(nextPowerup));

	World::WorldType type;
	worldState.read(reinterpret_cast<char*>(&type), sizeof(type));

	if (world == nullptr)
	{
		switch (type)
		{
		case World::Fixed:
			world = new FixedWorld();
			break;
		case World::Infinite:
			world = new InfiniteWorld();
			break;
		case World::FixedRepeating:
			world = new RepeatingFixedWorld();
			break;
		}
	}
	else
	{
		if (world->GetType() != type)
		{ //shouldn't ever happen, but don't allow loading a different type of world
			return;
		}
	}

	world->LoadState(worldState);
}

void TimedSurvivalManager::Save(std::string path)
{
	std::ofstream worldState{ path, std::ios::binary };

	worldState.write(reinterpret_cast<char*>(&score), sizeof(score));
	worldState.write(reinterpret_cast<char*>(&timer), sizeof(timer));
	worldState.write(reinterpret_cast<char*>(&duration), sizeof(duration));
	worldState.write(reinterpret_cast<char*>(&nextSpawn), sizeof(nextSpawn));
	worldState.write(reinterpret_cast<char*>(&nextPowerup), sizeof(nextPowerup));

	World::WorldType type = world->GetType();
	worldState.write(reinterpret_cast<char*>(&type), sizeof(type));

	world->SaveState(worldState);
}

unsigned int TimedSurvivalManager::GetScore()
{
	return score;
}

static Vector<float> GetOffscreenPos(Camera& camera, World* world, Sprite* sprite)
{
	Vector<float> topLeft = camera.GetCameraTopLeftWithoutZoom();
	Vector<int> cameraSize = (Vector<int>)camera.GetCameraViewSizeWithoutZoom();

	Vector<int> pos;

	Vector<int> spriteSize = sprite->GetSize().Ceil<int>();

	const int xVariance = cameraSize.x / 2 - spriteSize.x;
	const int yVariance = cameraSize.y / 2 - spriteSize.y;

	bool valid = false;

	//pick random edge, and keep trying until position is valid
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

bool TimedSurvivalManager::RunTick(InputHandler& input)
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
		if (e->GetHealth() <= 0)
		{ //clean up enemies here instead of world, so we can add score
			world->DespawnEnemy(i--, e);
			switch (e->GetType())
			{
				case Enemy::Basic:
					score += 2;
					break;
				case Enemy::Artillery:
					score += 5;
					break;
				case Enemy::Runner:
					score += 10;
					break;
				case Enemy::MineLayer:
					score += 5;
					break;
			}
			delete e;
		}
	}

	float oldTimer = timer;
	timer += input.GetDT();
	if (floor(oldTimer) < floor(timer))
		score += 1;

	while (timer > nextPowerup)
	{
		Powerup* p = new Powerup();
		p->SetTopLeftPosition(GetOffscreenPos(camera, world, p));
		world->SpawnPowerup(p);
		nextPowerup += (rand() % 1000) / 100.0f + 5;
	}

	while (timer > nextSpawn)
	{
		float cost;
		Enemy* enemy = factory.SpawnEnemy(&cost);

		enemy->SetTopLeftPosition(GetOffscreenPos(camera, world, enemy));

		world->SpawnEnemy(enemy);

		nextSpawn += (1 - (timer / duration) * 0.8) * cost;
	}

	return false;
}

void DrawBar(float threshold, int width, int height, Vector<int> position, unsigned char* color1, unsigned char* color2, unsigned char& alpha, Canvas& canvas)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i / (float)width < threshold)
				canvas.DrawPixelUnsafe(i + position.x, j + position.y, alpha, color1);
			else
				canvas.DrawPixelUnsafe(i + position.x, j + position.y, alpha, color2);
		}
	}
}

void TimedSurvivalManager::Draw(InputHandler& input)
{
	camera.UpdatePosition(input);
	camera.Redraw();

	std::string scoreText = std::to_string(score);
	int seconds = (int)timer % 60;
	int minutes = (int)timer / 60;
	std::string secondsText = std::to_string(seconds);
	if (secondsText.length() == 1)
		secondsText = "0" + secondsText;

	std::string timerText = std::to_string(minutes) + ":" + secondsText;

	int health = max(0,world->GetPlayer()->GetHealth());
	int maxHP = world->GetPlayer()->GetMaxHealth();
	std::string healthText = std::to_string(health) + "/" + std::to_string(maxHP);

	int fontSpacing = (Font::xGap + Font::letterSize.x);

	int x = canvas.getWidth() - 200;
	float x2 = x + 2;

	int timerWidth = fontSpacing * 6;
	float x3 = canvas.getWidth() - timerWidth / 2 - fontSpacing * timerText.length() / 2;

	float y1 = Font::letterSize.y + 8;

	canvas.DrawFont(scoreText, Vector<float>{ x2, y1 });

	unsigned char* red = new unsigned char[3] {255, 0, 0};
	unsigned char* green = new unsigned char[3] {0, 255, 0};
	unsigned char* gray = new unsigned char[3] {100, 100, 100};
	unsigned char* white = new unsigned char[3] {255, 255, 255};
	unsigned char alpha = 180;

	DrawBar(health / (float)maxHP, 200, Font::letterSize.y + 4, Vector<int>(x, 0), red, gray, alpha, canvas);

	int x5 = canvas.getWidth() - timerWidth;

	DrawBar(timer / duration, timerWidth, Font::letterSize.y + 4, Vector<int>(x5, Font::letterSize.y + 6), green, gray, alpha, canvas);

	canvas.DrawFont(timerText, Vector<float>{ x3, y1 });

	int x4 = x + 100 - healthText.length() * fontSpacing / 2;

	canvas.DrawFont(healthText, Vector<float>{ (float)x4, 2});

	DrawBar(1 - world->GetPlayer()->GetAoeCooldownPercent(), 200, Font::letterSize.y + 4, Vector<int>(x, canvas.getHeight() - Font::letterSize.y - 4), white, gray, alpha, canvas);
}
