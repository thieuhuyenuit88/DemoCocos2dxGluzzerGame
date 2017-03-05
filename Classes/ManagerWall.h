#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CManagerWall: public Node
{
public:
	CManagerWall(void);
	virtual ~CManagerWall(void);

	void InitWall();
	void StartScroll();
	void StopScroll();

	void SetSpeed(float speed){
		speedScroll = speed;
	}

	float GetSpeed(){return speedScroll;}
	
private:
	float speedScroll;

	Sprite* wall1;
	Sprite* wall2;
	Sprite* wall3;
	Sprite* wall4;
	Sprite* wall5;
	Sprite* wall6;

	void StartScrollWall1();
	void StartScrollWall2();
	void StartScrollWall3();
	void StartScrollWall4();
	void StartScrollWall5();
	void StartScrollWall6();

	void ReachedDestinationWall1();
	void ReachedDestinationWall2();
	void ReachedDestinationWall3();
	void ReachedDestinationWall4();
	void ReachedDestinationWall5();
	void ReachedDestinationWall6();
};

