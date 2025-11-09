#include "StressTester.h"
#include "FixedWorld.h"
#include "InfiniteWorld.h"
#include "RepeatingFixedWorld.h"
#include "font.h"

StressTester::StressTester(Canvas& canvas) : canvas(canvas), camera{ nullptr, canvas, &target }
{
}

void StressTester::Setup(World* _world)
{
	currentCount = 0;
	intendedCount = 1;
	world = _world;

	target.SetTarget(world->GetPlayer());
	camera.SetWorld(world);
}

void StressTester::Load(std::string path)
{
	std::ifstream worldState{ path, std::ios::binary };

	worldState.read(reinterpret_cast<char*>(&currentCount), sizeof(currentCount));
	worldState.read(reinterpret_cast<char*>(&intendedCount), sizeof(intendedCount));

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

void StressTester::Save(std::string path)
{
	std::ofstream worldState{ path, std::ios::binary };

	worldState.write(reinterpret_cast<char*>(&currentCount), sizeof(currentCount));
	worldState.write(reinterpret_cast<char*>(&intendedCount), sizeof(intendedCount));

	World::WorldType type = world->GetType();
	worldState.write(reinterpret_cast<char*>(&type), sizeof(type));

	world->SaveState(worldState);
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

bool StressTester::RunTick(InputHandler& input)
{
	world->Update(input);

	if (input.KeyDown('T'))
	{
		if (intendedCount < 1000)
			intendedCount *= 10;
		else
			intendedCount += 1000;
	}

	if (input.KeyDown('G'))
	{
		if (intendedCount <= 1000)
			intendedCount /= 10;
		else
			intendedCount -= 1000;
	}

	if (input.KeyHeld('C'))
	{
		for (int i = world->GetEnemyProjectiles().GetCurrentSize() - 1; i >= 0; i--)
		{
			Projectile* e = world->GetEnemyProjectiles()[i];
			world->DespawnProjectile(e);
			delete e;
		}
	}

	world->GetPlayer()->SetHealthScalar(intendedCount);
	world->GetPlayer()->Heal(world->GetPlayer()->GetMaxHealth());

	DynamicArray<Enemy*>& enemies = world->GetEnemies();
	for (unsigned int i = 0; i < enemies.GetCurrentSize(); i++)
	{
		Enemy* e = enemies[i];
		if (e->GetHealth() <= 0 || i >= intendedCount)
		{ //clean up enemies here instead of world, so we can add score
			world->DespawnEnemy(i--, e);
			delete e;
			currentCount--;
		}
	}

	while (currentCount < intendedCount)
	{
		float cost;
		Enemy* enemy = factory.SpawnEnemy(&cost);

		enemy->SetTopLeftPosition(GetOffscreenPos(camera, world, enemy));

		world->SpawnEnemy(enemy);

		currentCount++;
	}

	return false;
}

void StressTester::DrawBar(float threshold, int width, int height, Vector<int> position, unsigned char* color1, unsigned char* color2, unsigned char& alpha, Canvas& canvas)
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

void StressTester::Draw(InputHandler& input)
{
	camera.UpdatePosition(input);
	camera.Redraw();

	std::string scoreText = std::to_string(intendedCount);

	std::string timerText = std::to_string(world->GetEnemyProjectiles().GetCurrentSize());

	int health = max(0, world->GetPlayer()->GetHealth());
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

	canvas.DrawFont(timerText, Vector<float>{ x3, y1 });

	int x4 = x + 100 - healthText.length() * fontSpacing / 2;

	canvas.DrawFont(healthText, Vector<float>{ (float)x4, 2});

	DrawBar(1 - world->GetPlayer()->GetAoeCooldownPercent(), 200, Font::letterSize.y + 4, Vector<int>(x, canvas.getHeight() - Font::letterSize.y - 4), white, gray, alpha, canvas);
}
