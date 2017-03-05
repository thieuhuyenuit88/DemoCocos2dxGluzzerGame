#include "HealthBar.h"
#include "Constants.h"
#include "Guzzler.h"

HealthBar::HealthBar(void)
{
}


HealthBar::~HealthBar(void)
{
}

bool HealthBar::Init(Guzzler* guzzler, float _time){
	barHealth = Sprite::create("HealthBar.png");

	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("bloodPart.png");
	Texture2D::TexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
	texture->setTexParameters(&texParams);
	healthRay = Sprite::createWithTexture(texture, Rect(0, 0, 100, 16));
	healthRay->setColor(Color3B(255, 0, 10));

	timer = ProgressTimer::create(healthRay);
	this->addChild(timer);
	timer->setAnchorPoint(Vec2(0, 0.5f));
	timer->setType(ProgressTimer::Type::BAR);
	timer->setBarChangeRate(Vec2(1, 0));
	timer->setMidpoint(Vec2(0, 0.5));
	timer->setPercentage(100);
	timer->setPosition(Vec2(barHealth->getPositionX() - barHealth->getBoundingBox().size.width/2 + 5, 0));

	this->addChild(barHealth);
	
	ownGuzzler = guzzler;

	this->setPosition(0, ownGuzzler->getSpriteGuzzler()->getBoundingBox().size.height/2
		+ barHealth->getBoundingBox().size.height/2 + 10);
	
	//CCLOG("Full height: %f", ownGuzzler->getSpriteGuzzler()->getBoundingBox().size.height);
	
	ownGuzzler->addChild(this, kZHealthBar);

	timeProgress = _time;

	return true;


}

void HealthBar::Update(float dt){
	//CCLOG("Full height update: %f", ownGuzzler->getSpriteGuzzler()->getBoundingBox().size.height);
	
	this->setPosition(0, ownGuzzler->getSpriteGuzzler()->getBoundingBox().size.height/2
		+ barHealth->getBoundingBox().size.height/2 + 10);
}

void HealthBar::Release(){

}

void HealthBar::StartCountTime(){
	ProgressTo* to1 = ProgressTo::create(timeProgress, 0);
	CallFunc* countDone = CallFunc::create(CC_CALLBACK_0(HealthBar::FinishCountTime, this));
	auto seqActionTimer = Sequence::create(to1, countDone, nullptr);
	timer->runAction(seqActionTimer);
}

void HealthBar::StopCountTime(){
	timer->stopAllActions();
	ResetTimer();
}

void HealthBar::ResetTimer(){
	timer->setPercentage(100);
}

void HealthBar::FinishCountTime(){

}