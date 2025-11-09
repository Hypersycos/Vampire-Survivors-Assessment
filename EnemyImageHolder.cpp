#include "EnemyImageHolder.h"

EnemyImageHolder::EnemyImageHolder()
{
}

void EnemyImageHolder::Setup()
{
	std::string paths[6] = { "Resources/pink_body_squircle.png", "Resources/blue_body_rhombus.png", "Resources/red_body_circle.png", "Resources/green_body_square.png", "Resources/pink_body_rhombus.png", "Resources/pink_body_circle.png" };
	ImageHolder::Setup(paths);
}