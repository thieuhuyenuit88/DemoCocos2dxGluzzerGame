#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Guzzler;
class HealthBar: public Node
{
private:
	Sprite* barHealth;
	Sprite* healthRay;
	Guzzler* ownGuzzler;

	ProgressTimer* timer;
	float timeProgress;

	void FinishCountTime();
	void ResetTimer();
public:
	HealthBar(void);
	virtual ~HealthBar(void);

	void StartCountTime();
	void StopCountTime();

	bool Init(Guzzler* guzzler, float _time);

	void Update(float dt);

	void Release();


};

