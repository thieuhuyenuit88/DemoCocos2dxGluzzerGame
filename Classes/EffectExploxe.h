#pragma once
#include "cocos2d.h"

USING_NS_CC;

class EffectExploxe: public Node
{
private:
	Sprite* piece1;
	Sprite* piece2;
	Sprite* piece3;
	Sprite* piece4;
	Sprite* piece5;
public:
	EffectExploxe(void);
	virtual ~EffectExploxe(void);

	//create with autorelease
	static EffectExploxe* Create(Layer* layer);

	bool Init(Layer* layer);

	void StartExploxe();
	void StopExploxe();
	void SetSpeedExploxe(float timeDuration);
};

