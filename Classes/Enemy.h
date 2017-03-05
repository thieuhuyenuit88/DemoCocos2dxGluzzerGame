#pragma once
#include "MyObject.h"

USING_NS_CC;

class Guzzler;

class Enemy: public MyObject
{
private:
	Sprite* headEnemy;
	Sprite* bodyEnemy;
	Sprite* tailEnemy;

	int typeEnemy;

	float speed;
	float screenWidth;
	float xOffset;

	void ReachedDestination();
public:
	Enemy(void);
	Enemy(Layer* layer);
	virtual ~Enemy(void);

	bool isScored;
	bool isReached;

	bool Init(cocos2d::Layer *layer);

	void UpdateAnimation(float deltaTime);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	void UpdateStatus(float deltaTime);

	void Release();

	void Start();
	void Stop();
	void Initialise(const float _speed, const float _width);
	
	bool CheckCollideWithGuzzler(Guzzler* guzzler);
};

