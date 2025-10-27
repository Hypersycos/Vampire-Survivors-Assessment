#pragma once

#include "Sprite.cpp"

class Enemy : public Sprite
{
	float health;

public:
	float GetHealth()
	{
		return health;
	}
};