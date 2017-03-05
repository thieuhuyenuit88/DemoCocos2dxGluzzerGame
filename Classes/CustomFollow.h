#pragma once
#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;

class CustomFollow: public Follow
{
private:
	cocos2d::Rect curRectView;
	float curMarginHeight;
public:
	CustomFollow(void);
	virtual ~CustomFollow(void);

	cocos2d::Rect GetCurRectView(){
		return curRectView;
	}

	static CustomFollow* create(Node* followedNode, const float marginRect = kDesignResolutionHeight / 2);

	virtual void step(float dt) override;
};

