#pragma once
#include "FixedArray.h"
#include "Enemy.h"

class EnemyFactory
{
	FixedArray<int, 4> spawnWeights;
	FixedArray<float, 4> spawnCosts;
	int weightSum;

public:
	EnemyFactory();
	EnemyFactory(FixedArray<int, 4> spawnWeights, FixedArray<float, 4> spawnCosts);
	Enemy* SpawnEnemy(float* cost);
	static Enemy* CreateEnemy(unsigned char type);
	static Enemy* CreateEnemy(Enemy::Enemies type);
};