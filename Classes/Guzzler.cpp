#include "Guzzler.h"
#include "Constants.h"
#include "EffectExploxe.h"

Guzzler::Guzzler(void): MyObject()
{
}

Guzzler::Guzzler(cocos2d::Layer *layer):MyObject(){
	Init(layer);
}

Guzzler::~Guzzler(void)
{
}

bool Guzzler::Init(cocos2d::Layer *layer){
	//Position
	oPos = Point(GETWINSIZE_WIDTH / 4, GETWINSIZE_HEIGHT / 2);
	this->setPosition(oPos);

	//Init animation
	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("Guzzler.plist");
	auto spriteBatchNode = SpriteBatchNode::create("Guzzler.png");

	this->addChild(spriteBatchNode);

	guzzler = Sprite::createWithSpriteFrameName("Guzzler1.png");

	Vector<SpriteFrame *> aniNormalFrames(2);

	char strTemp[50] = {0};
	for (int i = 1; i<=2; i++)
	{
		sprintf(strTemp, "Guzzler%i.png", i);
		auto frame = cacher->getSpriteFrameByName(strTemp);
		aniNormalFrames.pushBack(frame);
	}

	Vector<SpriteFrame *> aniOpenMouthFrames(2);
	for (int i = 3; i<=5; i++)
	{
		sprintf(strTemp, "Guzzler%i.png", i);
		auto frame = cacher->getSpriteFrameByName(strTemp);
		aniOpenMouthFrames.pushBack(frame);
	}

	auto animationNormal = Animation::createWithSpriteFrames(aniNormalFrames, 0.4f);
	auto animationOpenMouth = Animation::createWithSpriteFrames(aniOpenMouthFrames, 0.025f);

	aniNormal = AdvanceAnimate::create(animationNormal);
	aniNormal->retain();
	aniOpenMouth = AdvanceAnimate::create(animationOpenMouth);
	aniOpenMouth->retain();
	aniCloseMouth = aniOpenMouth->reverse();
	aniCloseMouth->retain();

	spriteBatchNode->addChild(guzzler);

	guzzler->setColor(Color3B(227,220,112));

	layer->addChild(this, kZGuzzler);

	//Part mouth
	partMouth1 = Sprite::create("Mouth3.png");
	partMouth1->setAnchorPoint(Vec2(1, 0.5f));
	partMouth1->setPosition(guzzler->getBoundingBox().size.width/2, 0);
	partMouth1->setVisible(false);

	partMouth2 = Sprite::create("Mouth4.png");
	partMouth2->setAnchorPoint(Vec2(1, 0.5f));
	partMouth2->setPosition(guzzler->getBoundingBox().size.width/2, 0);
	partMouth2->setVisible(false);

	partMouth3 = Sprite::create("Mouth5.png");
	partMouth3->setAnchorPoint(Vec2(1, 0.5f));
	partMouth3->setPosition(guzzler->getBoundingBox().size.width/2, 0);
	partMouth3->setVisible(false);

	partMouth1->setColor(Color3B(227,220,112));
	partMouth2->setColor(Color3B(227,220,112));
	partMouth3->setColor(Color3B(227,220,112));

	this->addChild(partMouth1);
	this->addChild(partMouth2);
	this->addChild(partMouth3);

	//health Bar
	healthBar = new HealthBar;
	healthBar->Init(this, 2.0f);

	//collide
	isCollide = isAppearInCollide = isDisappearIncollide = false;

	containerLayer = layer;

	return true;
}

void Guzzler::Normal(){
	guzzler->stopAllActions();
	guzzler->runAction(RepeatForever::create(aniNormal));
	this->curSTT = sttGuzzlerNormal;
}

void Guzzler::OpenMouth(){
	guzzler->stopAllActions();
	CallFunc* actionDone = CallFunc::create(CC_CALLBACK_0(Guzzler::OpenDone, this));
	auto actionSequence = Sequence::create(aniOpenMouth, actionDone, nullptr);

	guzzler->runAction(actionSequence);
	this->curSTT = sttGuzzlerOpenningDontEat;
}

void Guzzler::CloseMouth(){
	guzzler->stopAllActions();
	CallFunc* actionDone = CallFunc::create(CC_CALLBACK_0(Guzzler::CloseDone, this));
	auto actionSequence = Sequence::create(aniCloseMouth, actionDone, nullptr);

	guzzler->runAction(actionSequence);
	this->curSTT = sttGuzzlerClosingDontEat;
	healthBar->StopCountTime();
}

void Guzzler::CloseDone(){
	//set frame 1 - normal
	guzzler->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Guzzler1.png"));
	Normal();
}

void Guzzler::OpenDone(){
	if (curSTT == sttGuzzlerOpenningEat)
	{
		this->curSTT = sttGuzzlerEating;
		partMouth3->setVisible(false);
	}else if (curSTT == sttGuzzlerOpenningDontEat)
	{
		this->curSTT = sttGuzzlerOpenDontEat;
		partMouth3->setVisible(true);
	}
	healthBar->StartCountTime();
}

void Guzzler::UpdateAnimation(float deltaTime){

}

void Guzzler::UpdateMove(float deltaTime)
{

}

void Guzzler::UpdateStatus(float deltaTime)
{

}

void Guzzler::ResetVisiblePartMouth(){
	partMouth1->setVisible(false);
	partMouth2->setVisible(false);
	partMouth3->setVisible(false);
}

void Guzzler::Update(float deltaTime){
	/*CCLOG("width of guzzler: %f", guzzler->getBoundingBox().size.width);*/

	int curFrame;
	switch (curSTT)
	{
	case sttGuzzlerOpenningDontEat:
		ResetVisiblePartMouth();
		curFrame = aniOpenMouth->getNextFrame();
		if (curFrame == 1)
		{
			partMouth1->setVisible(true);
		}else if (curFrame == 2)
		{
			partMouth2->setVisible(true);
		}else if (curFrame == 3)
		{
			partMouth3->setVisible(true);
		}
		break;
	/*case sttGuzzlerOpenDontEat:
		if (!partMouth3->isVisible())
		{
			ResetVisiblePartMouth();
			partMouth3->setVisible(true);
		}
		break;*/
	case sttGuzzlerOpenningEat:
	case sttGuzzlerClosingEat:
	case sttGuzzlerNormal:
		ResetVisiblePartMouth();
		break;
		/*case sttGuzzlerEating:
		partMouth3->setVisible(false);*/
		break;
	case sttGuzzlerClosingDontEat:
		ResetVisiblePartMouth();
		curFrame = aniCloseMouth->getNextFrame();
		if (curFrame == 1)
		{
			partMouth3->setVisible(true);
		}else if (curFrame == 2)
		{
			partMouth2->setVisible(true);
		}else if (curFrame == 3)
		{
			partMouth1->setVisible(true);
		}
		break;
	default:
		break;
	}

	//update collide
	if (isCollide)
	{
		switch (curSTT)
		{
		case sttGuzzlerOpenningDontEat:
		case sttGuzzlerOpenningEat:
		case sttGuzzlerClosingDontEat:
		case sttGuzzlerClosingEat:
		case sttGuzzlerNormal:
			curSTT = sttGuzzlerDeath;
			break;
		case sttGuzzlerOpenDontEat:
			curSTT = sttGuzzlerEating;
		case sttGuzzlerEating:
			if (isDisappearIncollide)
			{
				partMouth3->setVisible(false);
			}
			if (isAppearInCollide)
			{
				isDisappearIncollide = false;
				partMouth3->setVisible(true);
			}
			break;
		}
	}else{
		switch (curSTT)
		{
		case sttGuzzlerEating:
			curSTT = sttGuzzlerOpenDontEat;
			isAppearInCollide = false;
			break;
		}
	}

	//update health bar
	healthBar->Update(deltaTime);

	//update when death
	if (curSTT == sttGuzzlerDeath && prevSTT != sttGuzzlerDeath)
	{
		this->setVisible(false);
		auto explode = EffectExploxe::Create(containerLayer);
		explode->setPosition(this->getPositionX(), this->getPositionY());
		explode->StartExploxe();
	}

	prevSTT = curSTT;
}

void Guzzler::Release(){
	aniNormal->release();
	aniOpenMouth->release();
	aniCloseMouth->release();
}

Rect Guzzler::GetBoxCollision(){
	Rect convertNodeSpaceBox = BoundingBoxConvertedToNodeSpace(guzzler);
	return Rect(convertNodeSpaceBox.origin.x,
		convertNodeSpaceBox.origin.y,
		convertNodeSpaceBox.size.width,
		convertNodeSpaceBox.size.height);
}