#include "CCloud.h"


CCloud::CCloud(void)
{
}


CCloud::~CCloud(void)
{
}

CCloud* CCloud::createWithFile(char* fileName){
	auto sprite = new CCloud;
	if(sprite && sprite->initWithFile(fileName)){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void CCloud::Start(){
	this->stopAllActions();

	float currentX = this->getPositionX();
	float distance = currentX + xOffset;
	float time = distance / speed;
	Vec2 destination = Vec2(-xOffset, this->getPositionY());

	MoveTo *actionMove = MoveTo::create(time, destination);
	CallFunc *actionMoveDone = CallFunc::create(CC_CALLBACK_0(CCloud::ReachedDestination, this));
	this->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void CCloud::Stop(){
	this->stopAllActions();
}

void CCloud::SetSpeedAndWidth(const float _speed, const float _width){
	this->speed = _speed;
	this->screenWidth = _width;
	xOffset = 108; //this->getBoundingBox().size.width;
}

void CCloud::ReachedDestination(){
	this->setPositionX(xOffset + screenWidth);
	this->Start();
}
