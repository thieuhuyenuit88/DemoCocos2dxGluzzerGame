#pragma once
#include "cocos2d.h"

USING_NS_CC;

class AdvanceAnimate: public Animate
{
public:
	AdvanceAnimate();
	~AdvanceAnimate();
	
	int getNextFrame(){
		return _nextFrame;
	}

	virtual AdvanceAnimate* reverse() const override;
	static AdvanceAnimate* create(Animation *animation);
};
