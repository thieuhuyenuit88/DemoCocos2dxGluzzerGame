#include "CustomFollow.h"
#include "Constants.h"

CustomFollow::CustomFollow(void): Follow()
{
	curRectView = Rect(0, 0, GETWINSIZE_WIDTH, GETWINSIZE_HEIGHT);
	curMarginHeight = kDesignResolutionHeight / 2;
}

CustomFollow::~CustomFollow(void)
{
	CC_SAFE_RELEASE(_followedNode);
}

CustomFollow* CustomFollow::create(Node* followedNode, const float marginRect){
	CustomFollow* follow = new CustomFollow();
	follow->curMarginHeight = marginRect;
	if (follow && follow->initWithTarget(followedNode, Rect::ZERO))
	{
		follow->autorelease();
		return follow;
	}

	CC_SAFE_DELETE(follow);
	return nullptr;
}

void CustomFollow::step(float dt){
	CC_UNUSED_PARAM(dt);

	if (_boundarySet)
	{
		if (_boundaryFullyCovered)
		{
			return;
		}
		
		if (_followedNode->getPositionY() >= curMarginHeight)
		{
			float deltaPosY = _followedNode->getPositionY() - curMarginHeight;

			_target->setPositionY(clampf(_target->getPositionY() - deltaPosY, _bottomBoundary, _topBoundary));

			curMarginHeight = _followedNode->getPositionY();

			curRectView.setRect(curRectView.origin.x, curRectView.origin.y + deltaPosY, curRectView.size.width, curRectView.size.height);
		}

	}else {
		if (_followedNode->getPositionY() >= curMarginHeight)
		{
			float deltaPosY = _followedNode->getPositionY() - curMarginHeight;

			_target->setPositionY(_target->getPositionY() - deltaPosY);

			curMarginHeight = _followedNode->getPositionY();

			curRectView.setRect(curRectView.origin.x, curRectView.origin.y + deltaPosY, curRectView.size.width, curRectView.size.height);
		}
	}
}
