#pragma once
#include "cocos2d.h"

USING_NS_CC;

class TiledSprite:public Sprite
{
private:
	int width;
	int height;
public:
	TiledSprite(void);
	virtual ~TiledSprite(void);

	virtual bool init();

	static TiledSprite* initWithSprite(Sprite* p_sprite, int p_width, int p_height);
};

