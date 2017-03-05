#pragma once
#include "MyObject.h"

USING_NS_CC;

class DynamicObject: public MyObject
{
protected:
	/*Previous position*/
	Point prevPos;
public:
	DynamicObject(void);
	virtual ~DynamicObject(void);

	float getPrevPosX(){
		return prevPos.x;
	}

	float getPrevPosY(){
		return prevPos.y;
	}

	Point getPrevPos(){
		return prevPos;
	}

	virtual bool Init(cocos2d::Layer *layer){ return true; }
	/*virtual void ProcessCollision(MyObject* obj){}*/

	virtual void UpdateAnimation(float deltaTime){}
	virtual void UpdateStatus(float deltaTime){}
	virtual void UpdateMove(float deltaTime);
	virtual void Update(float deltaTime);

	virtual void Release();
};

