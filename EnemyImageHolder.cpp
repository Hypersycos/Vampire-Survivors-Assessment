#include "EnemyImageHolder.h"

EnemyImageHolder::EnemyImageHolder()
{
}

void EnemyImageHolder::Setup()
{
	std::string paths[4] = { "Resources/L2.png", "Resources/L2.png", "Resources/L2.png", "Resources/L2.png" };
	ImageHolder::Setup(paths);
}