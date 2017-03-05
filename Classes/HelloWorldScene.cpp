#include "HelloWorldScene.h"
#include "BackgroundLayer.h"
#include "Constants.h"
#include "CCManagerEnemy.h"
#include "CCManagerInGame.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	//add layer bg
	auto bgLayer = BackgroundLayer::create();
	scene->addChild(bgLayer);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto wall = new CManagerWall;
	this->addChild(wall);
	wall->StartScroll();
    
	guzzler = new Guzzler(this);
	guzzler->Normal();

	CCManagerInGame::GetInstance()->guzzlerInGame = guzzler;

	CCManagerEnemy::GetInstance()->InitListEnemies(this);
	CCManagerEnemy::GetInstance()->StartMove();

	//listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::OnHitOpen));
	isHolding = false;
    
	return true;
}

void HelloWorld::update(float dt){
	guzzler->Update(dt);

	CCManagerEnemy::GetInstance()->UpdateEnemies(dt);
}

void HelloWorld::OnHitOpen(float dt){
	if (isHolding)
	{
		
	}
	
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event){
	guzzler->OpenMouth();
	isHolding = true;
	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event){
	isHolding = false;
	guzzler->CloseMouth();
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event){

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
