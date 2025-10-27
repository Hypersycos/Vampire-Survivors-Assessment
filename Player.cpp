#include "Player.h"

//float GetEnemyHealth(Enemy* enemy)
//{
//	return enemy->GetHealth();
//}

	//void Update(float dt, World* world, InputHandler& input) override
	//{
	//	bool doAoE = aoeAttack.ApplyCooldown(dt, input.KeyDown(' '));

	//	Enemy* nearest = world->GetNearestEnemyToPlayer(autoAttack.range);
	//	bool doAttack = autoAttack.ApplyCooldown(dt, nearest != nullptr);

	//	if (doAttack)
	//	{
	//		//spawn projectile
	//	}
	// 
	//	if (doAoE)
	//	{
	//		Array<Enemy*> aoeEnemies = Array<Enemy>(aoeAttack.maxCount);
	//		world->GetNearestNEnemiesToPlayer(aoeAttack.maxCount, aoeEnemies, GetEnemyHealth);
	//		for (Enemy* e : aoeEnemies)
	//		{
	//			if (e != nullptr)
	//			{
	//				//damage e
	//			}
	//		}
	//	}
	//}