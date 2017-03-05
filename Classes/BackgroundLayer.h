#pragma once
#include "cocos2d.h"
#include "CCloud.h"

USING_NS_CC;

class BackgroundLayer: public LayerColor
{
private:
	/*Sprite* cloud1;
	Sprite* cloud2;
	Sprite* cloud3;
	Sprite* tree;
	Sprite* lamp;*/

	Vector<CCloud*> clouds;

	CCloud* AddCloud(const float speed, const Vec2 position,
		const int zIndex, char* fileName);
	void StartClouds();
	void StopClouds();
	void CreateClouds();
public:
	BackgroundLayer(void);
	virtual ~BackgroundLayer(void);

	virtual bool init();  

	CREATE_FUNC(BackgroundLayer);

	virtual void onEnter();
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);

	void SetColorBG(Color4B color);
};

