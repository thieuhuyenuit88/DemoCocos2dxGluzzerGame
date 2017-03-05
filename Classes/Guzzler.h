#pragma once
#include "MyObject.h"
#include "AdvanceAnimate.h"
#include "HealthBar.h"

USING_NS_CC;

class Guzzler: public MyObject
{
private:
	Sprite* guzzler;
	Sprite* partMouth1;
	Sprite* partMouth2;
	Sprite* partMouth3;
	HealthBar* healthBar;
	Layer* containerLayer;

	AdvanceAnimate* aniNormal;
	AdvanceAnimate* aniOpenMouth;
	AdvanceAnimate* aniCloseMouth;

	void initAnimation();
	void OpenDone();
	void CloseDone();
	void ResetVisiblePartMouth();
public:
	Guzzler(void);
	Guzzler(Layer* layer);
	virtual ~Guzzler(void);

	bool isCollide;
	bool isAppearInCollide;
	bool isDisappearIncollide;

	Sprite* getSpriteGuzzler(){
		return guzzler;
	}
	 
	AdvanceAnimate* getAnimationNormal(){
		return aniNormal;
	}

	AdvanceAnimate* getAnimationOpenMouth(){
		return aniOpenMouth;
	}

	AdvanceAnimate* getAnimationCloseMouth(){
		return aniCloseMouth;
	}

	void Normal();
	void OpenMouth();
	void CloseMouth();
	
	bool Init(cocos2d::Layer *layer);

	void UpdateAnimation(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	void UpdateStatus(float deltaTime);

	void Release();

	Rect GetBoxCollision();
};

