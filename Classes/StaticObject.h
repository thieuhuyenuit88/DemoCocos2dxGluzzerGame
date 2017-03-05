#pragma once
#include "MyObject.h"

class StaticObject: public MyObject
{
public:
	StaticObject(void);
	virtual ~StaticObject(void);

	virtual bool Init(cocos2d::Layer *layer){ return true; }
	/*virtual void ProcessCollision(MyObject* obj){}*/

	virtual void UpdateAnimation(float deltaTime){}
	virtual void UpdateStatus(float deltaTime){}
	virtual void Update(float deltaTime){}

	virtual void Release(){}
};

