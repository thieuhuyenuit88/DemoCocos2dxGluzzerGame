#include "CCManagerEnemy.h"
#include "CRandom.h"
#include "Constants.h"
#include "Enemy.h"

CCManagerEnemy::CCManagerEnemy(void)
{
}


CCManagerEnemy::~CCManagerEnemy(void)
{
}

void CCManagerEnemy::InitListEnemies(Layer *layer){
	containerLayer = layer;
	listEnemies = Vector<MyObject*>(10);

	for (int i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy(layer);
		enemy->setPosition(kStartPosEnemy, GETWINSIZE_HEIGHT / 2);
		enemy->Initialise(kSpeedEnemy, GETVISIBLESIZE_WIDTH);
		listEnemies.pushBack(enemy);
		enemy->release();
	}

	for (int i = 1; i < 10; i++)
	{
		float dis = CRandom::RandomBetweenIntRemoveBias(kDistanceMin, kDistanceMax);

		listEnemies.at(i)->setPositionX(listEnemies.at(i - 1)->getPositionX() + listEnemies.at(i - 1)->getFullBoundingBox().size.width + 25 + dis);
	}
}

void CCManagerEnemy::AddEnemies(){
	float posX = 0;
	float dis = CRandom::RandomBetweenIntRemoveBias(kDistanceMin, kDistanceMax);

	posX = listEnemies.back()->getPositionX() + listEnemies.back()->getFullBoundingBox().size.width + 25 + dis;

	Enemy* enemy = new Enemy(containerLayer);
	enemy->setPosition(posX, GETWINSIZE_HEIGHT / 2);
	enemy->Initialise(kSpeedEnemy, GETVISIBLESIZE_WIDTH);
	listEnemies.pushBack(enemy);
	enemy->Start();
	enemy->release();
}

void CCManagerEnemy::UpdateEnemies(float deltaTime){
	const Vector<MyObject*> copyEnemies = getCopyListEnemies();
	for (auto enemy: copyEnemies)
	{
		if (((Enemy*)enemy)->isReached == true)
		{
			listEnemies.eraseObject(enemy);
			enemy->Release();
			AddEnemies();
			break;
		}
	}

	for (auto enemy: listEnemies)
	{
		((Enemy*)enemy)->Update(deltaTime);
	}
}

void CCManagerEnemy::StartMove(){
	for (auto enemy: listEnemies)
	{
		((Enemy*)enemy)->Start();
	}
}

void CCManagerEnemy::StopMove(){
	for (auto enemy: listEnemies)
	{
		((Enemy*)enemy)->Stop();
	}
}

void CCManagerEnemy::Release(){
	listEnemies.clear();
	Destroy();
}