#include "EnemyImageHolder.h"

EnemyImageHolder::EnemyImageHolder()
{
}

void EnemyImageHolder::Setup()
{
	std::string paths[4] = { "Resources/pink_body_squircle.png", "Resources/blue_body_rhombus.png", "Resources/red_body_circle.png", "Resources/green_body_square.png" };
	ImageHolder::Setup(paths);
}