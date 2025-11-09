#include "EnemyFactory.h"
#include "BasicEnemy.h"
#include "Runner.h"
#include "Artillery.h"
#include "MineLayer.h"

EnemyFactory::EnemyFactory() : EnemyFactory({ 5, 1, 1, 1 }, {1, 4, 2, 2})
{
}

EnemyFactory::EnemyFactory(FixedArray<int, 4> spawnWeights, FixedArray<float, 4> spawnCosts) : spawnWeights(spawnWeights), spawnCosts(spawnCosts)
{
	weightSum = 0;
	for (int weight : spawnWeights)
		weightSum += weight;
}

Enemy* EnemyFactory::SpawnEnemy(float* cost)
{
	int choice = rand() % weightSum;
	for (int i = 0; i < 4; i++)
	{
		if (choice < spawnWeights[i])
		{
			*cost = 1;// spawnCosts[i];
			return CreateEnemy(i);
		}
		choice -= spawnWeights[i];
	}
	*cost = 1;
	return CreateEnemy(0);
}

Enemy* EnemyFactory::CreateEnemy(Enemy::Enemies type)
{
	switch (type)
	{
	case Enemy::Artillery:
		return new Artillery();
	case Enemy::Runner:
		return new Runner();
	case Enemy::MineLayer:
		return new MineLayer();
	case Enemy::Basic:
	default:
		return new BasicEnemy();
	}
}

Enemy* EnemyFactory::CreateEnemy(unsigned char type)
{
	switch (type)
	{
	case 1:
		return new Runner();
	case 2:
		return new Artillery();
	case 3:
		return new MineLayer();
	case 0:
	default:
		return new BasicEnemy();
	}
}
