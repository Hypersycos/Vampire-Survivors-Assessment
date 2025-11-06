#include "World.h"

World::World(std::string* tiles, unsigned int count) : enemyCount(0), tileImages(Array<GamesEngineeringBase::Image>(count))
{
	if (tiles != nullptr)
		LoadImages(tiles, count, true);
}

void World::LoadImages(std::string* tiles, unsigned int count, bool freeTiles)
{
	for (unsigned int i = 0; i < count; i++)
	{
		tileImages[i].load(tiles[i]);
	}
	if (freeTiles)
		delete[] tiles;
}

int World::TileAt(Vector<int> position)
{
	int X = (int)round(position.x / (float)tileSize);
	return this->TileAt((int)round(position.x / (float)tileSize), (int)round(position.y / (float)tileSize));
}

int World::TileAtGrid(Vector<int> position)
{
	return TileAt(position.x, position.y);
}

int World::TileAt(Vector<float> position)
{
	return this->TileAt((int)round(position.x / (float)tileSize), (int)round(position.y / (float)tileSize));
}

GamesEngineeringBase::Image* World::GetTileImage(int index)
{
	return &tileImages[index];
}

int World::GetTileSize() const
{
	return tileSize;
}

Player* World::GetPlayer() const
{
	return player;
}

void World::SetPlayer(Player* player)
{
	this->player = player;
}

DynamicArray<Enemy*>& World::GetEnemies()
{
	return enemies;
}

DynamicArray<Projectile*>& World::GetPlayerProjectiles()
{
	return playerProjectiles;
}

DynamicArray<Projectile*>& World::GetEnemyProjectiles()
{
	return enemyProjectiles;
}

Enemy* World::GetNearestEnemy(float maxRange, Vector<float> position)
{
	Enemy* nearest = nullptr;
	float nearestDistance = maxRange * maxRange + 1;

	for (Enemy* enemy : enemies)
	{
		if (enemy != nullptr)
		{
			float distance = (enemy->GetPosition() - position).sqrMagnitude();
			if (distance < nearestDistance)
			{
				nearest = enemy;
				nearestDistance = distance;
			}
		}
	}

	return nearest;
}

Enemy* World::GetNearestEnemyToPlayer(float maxRange)
{
	return GetNearestEnemy(maxRange, player->GetPosition());
}

void World::GetNearestNEnemies(float maxRange, Vector<float> position, Array<Enemy*>& arr, Comparer comparer)
{
	int N = arr.GetSize();
	if (N == 0)
		return;

	float* distArr = new float[N] {};
	for (int i = 0; i < N; i++)
	{
		arr[i] = nullptr;
	}

	for (Enemy* enemy : enemies)
	{
		if ((enemy->GetPosition() - position).sqrMagnitude() <= maxRange * maxRange)
		{
			float distance = comparer(enemy);
			int i = N - 1;
			while (i >= 0 && (arr[i] == nullptr || distArr[i] > distance))
			{
				if (i < N - 1)
				{
					distArr[i+1] = distArr[i];
					arr[i+1] = arr[i];
				}
					
				distArr[i] = distance;
				arr[i--] = enemy;
			}
		}
	}
}

void World::GetNearestNEnemiesToPlayer(float maxRange, Array<Enemy*>& arr, Comparer comparer)
{
	return GetNearestNEnemies(maxRange, player->GetPosition(), arr, comparer);
}

void World::Update(InputHandler& inputHandler)
{
	player->Update(this, inputHandler);

	for (Projectile* p : playerProjectiles)
	{
		p->Update(this, inputHandler);
	}

	for (int i = 0; i < enemies.GetCurrentSize(); i++)
	{
		Enemy* e = enemies[i];
		e->Update(this, inputHandler);
		for (int j = 0; j < playerProjectiles.GetCurrentSize(); j++)
		{
			Projectile* p = playerProjectiles[j];
			if (p->checkCollision(e))
			{
				if (e->Damage(p->GetDamage()))
				{
					DespawnEnemy(i--, e);
					delete e;
					DespawnProjectile(j--, p);
					delete p;
					break;
				}
				DespawnProjectile(j--, p);
				delete p;
			}
		}
	}

	for (int i = 0; i < enemyProjectiles.GetCurrentSize(); i++)
	{
		Projectile* p = enemyProjectiles[i];
		p->Update(this, inputHandler);
		if (p->checkCollision(player))
		{
			if (player->Damage(p->GetDamage()))
				break;
			DespawnProjectile(i--, p);
			delete p;
		}
	}
}

void World::SpawnEnemy(Enemy* enemy)
{
	enemies.Add(enemy);
	enemy->enabled = true;
}

void World::SpawnProjectile(Projectile* projectile)
{
	if (projectile->getLayer() == CollidesWithEnemies)
	{
		playerProjectiles.Add(projectile);
	}
	else
	{
		enemyProjectiles.Add(projectile);
	}
	projectile->enabled = true;
}

bool World::DespawnProjectile(Projectile* projectile)
{
	projectile->enabled = false;
	if (projectile->getLayer() == CollidesWithEnemies)
	{
		return playerProjectiles.Remove(projectile);
	}
	else
	{
		return enemyProjectiles.Remove(projectile);
	}
}

bool World::DespawnProjectile(unsigned int i, Projectile* projectile)
{
	if (projectile->getLayer() == CollidesWithEnemies)
	{
		if (playerProjectiles[i] == projectile)
		{
			projectile->enabled = false;
			return playerProjectiles.Remove(projectile);
		}
	}
	else
	{
		if (enemyProjectiles[i] == projectile)
		{
			projectile->enabled = false;
			return enemyProjectiles.Remove(projectile);
		}
	}
	return false;
}

bool World::DespawnEnemy(Enemy* enemy)
{
	enemy->enabled = false;
	return enemies.Remove(enemy);
}

bool World::DespawnEnemy(unsigned int i, Enemy* enemy)
{
	if (enemies[i] == enemy)
	{
		enemy->enabled = false;
		return enemies.Remove(enemy);
	}
	else
	{
		return false;
	}
}

void World::TryMove(CollisionSprite* sprite, Vector<float> change)
{
	Array<Vector<float>> checks{ 4 };

	Vector<float> target = sprite->GetPosition() + change;

	for (int i = 0; i < 4; i++)
		checks[i] = sprite->GetPosition() + change;

	checks[0].x += sprite->GetRadius();
	checks[1].y += sprite->GetRadius();
	checks[2].x -= sprite->GetRadius();
	checks[3].y -= sprite->GetRadius();

	for (int i = 0; i < 4; i++)
	{
		int tile = TileAt(checks[i]);
		bool canMove = tile >= 0;//&& tileValues[tile].collisionMatrix[sprite->getLayer()];
		if (!canMove)
		{
			if ((checks[i] - target).x < 0.001)
			{
				change.x = 0;
			}
			else
			{
				change.y = 0;
			}
		}
	}
	sprite->Move(change);
}

//void World::TryMove(CollisionSprite* sprite, Vector<float> change)
//{
//	int tileSize = (int)this->tileSize;
//	//sprite->SetPosition(Vector<int>(99 * tileSize, 0));
//
//	//change = Vector<float>(16, 0);
//
//	Array<Vector<int>> grids = { 9 };
//	grids[4] = (sprite->GetPosition() / (float)tileSize).Round<int>();
//	Vector<float> currentPos = sprite->GetPosition();
//	Vector<int> target = (sprite->GetPosition() + change / tileSize).Floor<int>();
//	int targetIndex;
//	int k = -1;
//	for (int i = -1; i <= 1; i++)
//	{
//		for (int j = -1; j <= 1; j++)
//		{
//			k++;
//			if (i == 0 && j == 0)
//				continue;
//			grids[k] = grids[4] + Vector<int>(i, j);
//			if (grids[k] == target)
//				targetIndex = k;
//		}
//	}
//
//	Array<bool> canMove = { 9 };
//	bool anyRestrictions = false;
//	for (int i = 0; i < 9; i++)
//	{
//		int tile = TileAtGrid(grids[i]);
//		canMove[i] = tile >= 0;//&& tileValues[tile].collisionMatrix[sprite->getLayer()];
//		anyRestrictions = anyRestrictions || !canMove[i];
//	}
//
//	if (!anyRestrictions)
//		sprite->Move(change);
//	else
//	{
//		for (int i = -1; i <= 1; i++)
//		{
//			for (int j = -1; j <= 1; j++)
//			{
//				if (i == 0 && j == 0)
//					continue;
//				int k = j + 1 + (i + 1) * 3;
//				if (canMove[k])
//					continue;
//
//				if (i != 0)
//				{
//
//					Vector<float> targetPos = sprite->GetPosition() + change;
//
//					float boundaryX = grids[4].x * tileSize + i * tileSize / 2;
//					float boundaryY1 = grids[4].y * tileSize + tileSize / 2;
//					float boundaryY2 = grids[4].y * tileSize - tileSize / 2;
//					float dist = (boundaryX - targetPos.x) * i;
//					if (dist < sprite->GetRadius())
//					{					
//						//y^2 + y * (-2playerY) + (playerY^2 - collR^2 + (boundaryX - playerX)^2) = 0
//
//						//y = (-b + / -sqrt(b ^ 2 - 4ac)) / 
//
//						float a = 1;
//						float b = -2 * targetPos.y;
//						float c = targetPos.y * targetPos.y - sprite->GetRadius() * sprite->GetRadius() + (boundaryX - targetPos.x) * (boundaryX - targetPos.x);
//
//
//						float y1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
//						float y2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
//
//						bool intersect1 = y1 < boundaryY1 && y1 > boundaryY2;
//
//						bool intersect2 = y2 < boundaryY1 && y2 > boundaryY2;
//
//						if (intersect1 && intersect2)
//						{
//							change.x += (dist - sprite->GetRadius()) * i;
//						}
//						else if (intersect1)
//						{
//							change += Vector<float>(boundaryX, y1) - targetPos;
//						}
//						else if (intersect2)
//						{
//							change += Vector<float>(boundaryX, y2) - targetPos;
//						}
//					}
//				}
//
//				if (j != 0)
//				{
//
//					Vector<float> targetPos = sprite->GetPosition() + change;
//
//					float boundaryY = grids[4].y * tileSize + j * tileSize / 2;
//					float boundaryX1 = grids[4].x * tileSize + tileSize / 2;
//					float boundaryX2 = grids[4].x * tileSize - tileSize / 2;
//					float dist = (boundaryY - targetPos.y) * j;
//					if (dist < sprite->GetRadius())
//					{
//						//y^2 + y * (-2playerY) + (playerY^2 - collR^2 + (boundaryX - playerX)^2) = 0
//
//						//y = (-b + / -sqrt(b ^ 2 - 4ac)) / 
//
//						float a = 1;
//						float b = -2 * targetPos.x;
//						float c = targetPos.x * targetPos.x - sprite->GetRadius() * sprite->GetRadius() + (boundaryY - targetPos.y) * (boundaryY - targetPos.y);
//
//
//						float x1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
//						float x2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
//
//						bool intersect1 = x1 < boundaryX1 && x1 > boundaryX2;
//
//						bool intersect2 = x2 < boundaryX1 && x2 > boundaryX2;
//
//						if (intersect1 && intersect2)
//						{
//							change.y += (dist - sprite->GetRadius() + 1) * j;
//						}
//						else if (intersect1)
//						{
//							change += Vector<float>(x1, boundaryY) - targetPos;
//						}
//						else if (intersect2)
//						{
//							change += Vector<float>(x2, boundaryY) - targetPos;
//						}
//					}
//				}
//			}
//		}
//		sprite->Move(change);
//	}
//}
