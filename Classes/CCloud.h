#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CCloud: public Sprite
{
public:
	CCloud(void);
	virtual ~CCloud(void);

	int state;

	static CCloud* createWithFile(char* fileName);

	void Start();
	void Stop();
	void SetSpeedAndWidth(const float _speed, const float _width);
private:
	void ReachedDestination();

	float startPosX;
	float speed;
	float screenWidth;
	float pixelPerSec;
	float xOffset;
};

