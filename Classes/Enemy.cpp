#include "Enemy.h"
#include "Constants.h"
#include "CRandom.h"
#include "Guzzler.h"
#include "CCManagerInGame.h"

Enemy::Enemy(void): MyObject()
{
}


Enemy::~Enemy(void)
{
}

Enemy::Enemy(cocos2d::Layer *layer):MyObject(){
	Init(layer);
}

bool Enemy::Init(cocos2d::Layer *layer){
	//Position
	oPos = Point(GETWINSIZE_WIDTH / 2 + 100, GETWINSIZE_HEIGHT / 2);
	this->setPosition(oPos);
	
	//Get random type
	typeEnemy = CRandom::RandomBetweenIntRemoveBias(kTypeEnemy1, kTypeEnemy5);

	//CCLOG("type Enemy: %d", typeEnemy);

	//Init animation
	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("EnemyHead.plist");
	auto spriteBatchNode = SpriteBatchNode::create("EnemyHead.png");

	this->addChild(spriteBatchNode);

	if (typeEnemy == kTypeEnemy1)
	{
		headEnemy = Sprite::createWithSpriteFrameName("EnemyHead1.png");
		headEnemy->setFlippedX(true);

		Vector<SpriteFrame *> framesEnemyType1(2);

		char strTemp[50] = {0};
		for (int i = 1; i<=2; i++)
		{
			sprintf(strTemp, "EnemyHead%i.png", i);
			auto frame = cacher->getSpriteFrameByName(strTemp);
			framesEnemyType1.pushBack(frame);
		}

		auto animationType1 = Animation::createWithSpriteFrames(framesEnemyType1, 0.4f);
		headEnemy->runAction(RepeatForever::create(Animate::create(animationType1)));
	}else{
		headEnemy = Sprite::createWithSpriteFrameName("EnemyHead3.png");
		headEnemy->setFlippedX(true);

		Vector<SpriteFrame *> framesEnemyOthers(2);

		char strTemp[50] = {0};
		for (int i = 3; i<=4; i++)
		{
			sprintf(strTemp, "EnemyHead%i.png", i);
			auto frame = cacher->getSpriteFrameByName(strTemp);
			framesEnemyOthers.pushBack(frame);
		}

		auto animationOthers = Animation::createWithSpriteFrames(framesEnemyOthers, 0.4f);
		headEnemy->runAction(RepeatForever::create(Animate::create(animationOthers)));
	}

	spriteBatchNode->addChild(headEnemy);
	
	headEnemy->setColor(Color3B(57, 147, 224));

	layer->addChild(this, kZIndexEnemy);
	
	//part other - if have
	switch (typeEnemy)
	{
	case kTypeEnemy2:
		tailEnemy = Sprite::create("EnemyTail-Tint.png");
		tailEnemy->setFlippedX(true);
		tailEnemy->setPositionX(tailEnemy->getBoundingBox().size.width - 1);
		tailEnemy->setColor(Color3B(57, 147, 224));
		this->addChild(tailEnemy);
		break;
	case kTypeEnemy3:
	case kTypeEnemy4:
	case kTypeEnemy5:
		tailEnemy = Sprite::create("EnemyTail-Tint.png");
		tailEnemy->setFlippedX(true);
		tailEnemy->setPositionX(tailEnemy->getBoundingBox().size.width * (typeEnemy - 1) - 1);
		tailEnemy->setColor(Color3B(57, 147, 224));
		this->addChild(tailEnemy);

		for(int i = 1; i <= (typeEnemy - 2); i++){
			bodyEnemy = Sprite::create("EnemyBody-Tint.png");
			bodyEnemy->setPositionX(tailEnemy->getBoundingBox().size.width * i - 1);
			bodyEnemy->setColor(Color3B(57, 147, 224));
			this->addChild(bodyEnemy);
		}
		break;
	}

	curSTT = prevSTT = kSttEnemyNormal;

	return true;
}

void Enemy::UpdateAnimation(float deltaTime){

}

void Enemy::UpdateMove(float deltaTime){

}

void Enemy::Update(float deltaTime){
	if (CheckCollideWithGuzzler(CCManagerInGame::GetInstance()->guzzlerInGame))
	{
		curSTT = kSttEnemyCollide;
	}else{
		curSTT = kSttEnemyNormal;
	}

	if (curSTT == kSttEnemyCollide && prevSTT == kSttEnemyNormal)
	{
		CCManagerInGame::GetInstance()->guzzlerInGame->isCollide = true;
	}
	else if (curSTT == kSttEnemyNormal && prevSTT == kSttEnemyCollide
		&& isScored == false && CCManagerInGame::GetInstance()->guzzlerInGame->getCurSTT() == sttGuzzlerEating)
	{
		CCManagerInGame::GetInstance()->guzzlerInGame->isCollide = false;
		CCManagerInGame::GetInstance()->scoreGame += 1;
		isScored = true;
	}

	if (curSTT == kSttEnemyCollide &&
		this->getFullBoundingBox().origin.x + this->getFullBoundingBox().size.width <= 
		CCManagerInGame::GetInstance()->guzzlerInGame->getPositionX() + 12)
	{
		CCManagerInGame::GetInstance()->guzzlerInGame->isAppearInCollide = true;
	}

	if (curSTT == kSttEnemyCollide &&
		this->getFullBoundingBox().origin.x <= 
		CCManagerInGame::GetInstance()->guzzlerInGame->getPositionX() + 12)
	{
		CCManagerInGame::GetInstance()->guzzlerInGame->isDisappearIncollide = true;
	}

	prevSTT = curSTT;
}

void Enemy::UpdateStatus(float deltaTime){

}

void Enemy::Release(){
	this->removeFromParent();
}

void Enemy::Start(){
	this->stopAllActions();

	float currentX = this->getPositionX();
	float distance = currentX + xOffset;
	float time = distance / speed;
	Vec2 destination = Vec2(-xOffset, this->getPositionY());

	MoveTo *actionMove = MoveTo::create(time, destination);
	CallFunc *actionMoveDone = CallFunc::create(CC_CALLBACK_0(Enemy::ReachedDestination, this));
	this->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void Enemy::Stop(){
	this->stopAllActions();
}

void Enemy::Initialise(const float _speed, const float _width){
	this->speed = _speed;
	this->screenWidth = _width;
	xOffset = this->getFullBoundingBox().size.width;
	isScored = false;
	isReached = false;
}

void Enemy::ReachedDestination(){
	isReached = true;
}

bool Enemy::CheckCollideWithGuzzler(Guzzler* guzzler){
	if (this->getFullBoundingBox().intersectsRect(guzzler->GetBoxCollision()))
	{
		return true;
	}else{
		return false;
	}
}