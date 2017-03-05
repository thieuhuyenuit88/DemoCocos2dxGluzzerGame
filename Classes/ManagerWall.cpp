#include "ManagerWall.h"
#include "Constants.h"

CManagerWall::CManagerWall(void)
{
	speedScroll = 4.0f;
	InitWall();
}


CManagerWall::~CManagerWall(void)
{
}

void CManagerWall::InitWall(){
	wall1 = Sprite::create("Wall.png");
	wall2 = Sprite::create("Wall.png");
	wall3 = Sprite::create("Wall.png");
	wall4 = Sprite::create("Wall.png");
	wall5 = Sprite::create("Wall.png");
	wall6 = Sprite::create("Wall.png");

	wall1->setFlippedY(true);
	wall1->setAnchorPoint(Vec2(0, 0));
	wall1->setPosition(Vec2(0, 0));
	this->addChild(wall1, kZIndexWall);

	wall2->setFlippedY(true);
	wall2->setAnchorPoint(Vec2(0, 0));
	wall2->setPosition(Vec2(wall2->getBoundingBox().size.width, 0));
	this->addChild(wall2, kZIndexWall);

	wall3->setFlippedY(true);
	wall3->setAnchorPoint(Vec2(0, 0));
	wall3->setPosition(Vec2(wall3->getBoundingBox().size.width * 2, 0));
	this->addChild(wall3, kZIndexWall);

	wall4->setAnchorPoint(Vec2(0, 1));
	wall4->setPosition(Vec2(0, GETWINSIZE_HEIGHT));
	this->addChild(wall4, kZIndexWall);

	wall5->setAnchorPoint(Vec2(0, 1));
	wall5->setPosition(Vec2(wall5->getBoundingBox().size.width, GETWINSIZE_HEIGHT));
	this->addChild(wall5, kZIndexWall);

	wall6->setAnchorPoint(Vec2(0, 1));
	wall6->setPosition(Vec2(wall6->getBoundingBox().size.width * 2, GETWINSIZE_HEIGHT));
	this->addChild(wall6, kZIndexWall);
}

void CManagerWall::StartScrollWall1(){
	wall1->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(-wall1->getBoundingBox().size.width, 0));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(CManagerWall::ReachedDestinationWall1, this));
	wall1->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void CManagerWall::StartScrollWall2(){
	wall2->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(-wall2->getBoundingBox().size.width, 0));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(CManagerWall::ReachedDestinationWall2, this));
	wall2->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void CManagerWall::StartScrollWall3(){
	wall3->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(-wall3->getBoundingBox().size.width, 0));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(CManagerWall::ReachedDestinationWall3, this));
	wall3->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void CManagerWall::StartScrollWall4(){
	wall4->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(-wall4->getBoundingBox().size.width, 0));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(CManagerWall::ReachedDestinationWall4, this));
	wall4->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void CManagerWall::StartScrollWall5(){
	wall5->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(-wall5->getBoundingBox().size.width, 0));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(CManagerWall::ReachedDestinationWall5, this));
	wall5->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void CManagerWall::StartScrollWall6(){
	wall6->stopAllActions();

	MoveBy* actionMoveBy = MoveBy::create(speedScroll, Vec2(-wall6->getBoundingBox().size.width, 0));
	CallFunc* actionMoveDone = CallFunc::create(CC_CALLBACK_0(CManagerWall::ReachedDestinationWall6, this));
	wall6->runAction(Sequence::create(actionMoveBy, actionMoveDone, NULL));
}

void CManagerWall::ReachedDestinationWall1(){
	wall1->setPosition(Vec2(0, 0));
	StartScrollWall1();
}

void CManagerWall::ReachedDestinationWall2(){
	wall2->setPosition(Vec2(wall2->getBoundingBox().size.width, 0));
	StartScrollWall2();
}

void CManagerWall::ReachedDestinationWall3(){
	wall3->setPosition(Vec2(wall3->getBoundingBox().size.width * 2, 0));
	StartScrollWall3();
}

void CManagerWall::ReachedDestinationWall4(){
	wall4->setPosition(Vec2(0, GETWINSIZE_HEIGHT));
	StartScrollWall4();
}

void CManagerWall::ReachedDestinationWall5(){
	wall5->setPosition(Vec2(wall5->getBoundingBox().size.width, GETWINSIZE_HEIGHT));
	StartScrollWall5();
}

void CManagerWall::ReachedDestinationWall6(){
	wall6->setPosition(Vec2(wall6->getBoundingBox().size.width * 2, GETWINSIZE_HEIGHT));
	StartScrollWall6();
}

void CManagerWall::StopScroll(){
	wall1->stopAllActions();
	wall2->stopAllActions();
	wall3->stopAllActions();
	wall4->stopAllActions();
	wall5->stopAllActions();
	wall6->stopAllActions();
}

void CManagerWall::StartScroll(){
	StartScrollWall1();
	StartScrollWall2();
	StartScrollWall3();
	StartScrollWall4();
	StartScrollWall5();
	StartScrollWall6();
}