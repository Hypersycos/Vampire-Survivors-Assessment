#pragma once

#include "Character.h"
#include "EnemyImageHolder.h"

class Enemy : public Character
{
	static EnemyImageHolder ImageHolder;

	void Serialize(std::ofstream& stream) override;

	void Deserialize(std::ifstream& stream) override;
};