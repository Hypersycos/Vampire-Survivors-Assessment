#include "EnemyFactory.h"
#include "BasicEnemy.h"
#include "Runner.h"
#include "Artillery.h"

Enemy* SpawnHelper(int i)
{
	switch (i)
	{
	case 0:
		return new BasicEnemy();
	case 1:
		return new Runner();
	case 2:
		return new Artillery();
	case 3:
		return new BasicEnemy();
	default:
		return new BasicEnemy();
	}
}

EnemyFactory::EnemyFactory() : EnemyFactory({ 5, 1, 1, 0 }, {1, 4, 2, 1})
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
			return SpawnHelper(i);
		}
		choice -= spawnWeights[i];
	}
	*cost = 1;
	return SpawnHelper(0);
}
