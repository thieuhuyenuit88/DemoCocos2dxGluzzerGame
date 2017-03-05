#include "AdvanceAnimate.h"

AdvanceAnimate::AdvanceAnimate():Animate(){

}

AdvanceAnimate::~AdvanceAnimate(){
	CC_SAFE_RELEASE(_animation);
	CC_SAFE_RELEASE(_origFrame);
	CC_SAFE_DELETE(_splitTimes);
	CC_SAFE_RELEASE(_frameDisplayedEvent);
}

AdvanceAnimate* AdvanceAnimate::create(Animation *animation)
{
	AdvanceAnimate *animate = new AdvanceAnimate();
	animate->initWithAnimation(animation);
	animate->autorelease();

	return animate;
}

AdvanceAnimate* AdvanceAnimate::reverse() const
{
	auto oldArray = _animation->getFrames();
	Vector<AnimationFrame*> newArray(oldArray.size());

	if (oldArray.size() > 0)
	{
		for (auto iter = oldArray.crbegin(); iter != oldArray.crend(); ++iter)
		{
			AnimationFrame* animFrame = *iter;
			if (!animFrame)
			{
				break;
			}

			newArray.pushBack(animFrame->clone());
		}
	}

	Animation *newAnim = Animation::create(newArray, _animation->getDelayPerUnit(), _animation->getLoops());
	newAnim->setRestoreOriginalFrame(_animation->getRestoreOriginalFrame());
	return AdvanceAnimate::create(newAnim);
}