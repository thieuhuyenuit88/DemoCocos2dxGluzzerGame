#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include "MyObject.h"

USING_NS_CC;

class CCManagerEnemy: public Singleton<CCManagerEnemy>
{
private:
	Vector<MyObject*> listEnemies;
	Layer* containerLayer;

	const Vector<MyObject*> & getCopyListEnemies(){
		return listEnemies;
	};

	void AddEnemies();
public:
	CCManagerEnemy(void);
	virtual ~CCManagerEnemy(void);

	Vector<MyObject*> GetListEnemies(){
		return listEnemies;
	}

	void StartMove();
	void StopMove();

	void InitListEnemies(Layer *layer);

	void UpdateEnemies(float deltaTime);

	void Release();
};

