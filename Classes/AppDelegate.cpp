#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "CRandom.h"
#include "Constants.h"
#include <vector>
#include <string>

USING_NS_CC;
using namespace std;

typedef struct tagResource
{
	Size size;
	char directory[32];
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "RS480x320" };
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "RS1024x768"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "RS2048x1536" };
static cocos2d::Size designResolutionSize = cocos2d::CCSizeMake(kDesignResolutionWidth, kDesignResolutionHeight);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// initialize random
	CRandom::InitRandom();

	// initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		Rect sizeFrame = Rect(0, 0, 1440, 900);
		char title[32];
		memset(title, 0, sizeof(title));
		sprintf(title, "Guzzler %4.1fx%4.1f", sizeFrame.size.width, sizeFrame.size.height);

        glview = GLView::createWithRect(title, sizeFrame);
        director->setOpenGLView(glview);
    }

	////////////////////////////////////////////////////////////////////////////
	///////////////////////////FIXED HEIGHT////////////////////////////////////	
	//////////////////////////////////////////////////////////////////////////
	
	Size frameSize = glview->getFrameSize();

	// Transform from design resolution to screen resolution - fixed height
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedHeight);
#endif

	vector<string> searchPath;

	// Transform from resource resolution to design resolution - according height size
	// if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > mediumResource.size.height)
	{
		searchPath.push_back(largeResource.directory);

		director->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
	}
	// if the frame's height is larger than the height of small resource size, select medium resource.
	else if (frameSize.height > smallResource.size.height)
	{
		searchPath.push_back(mediumResource.directory);

		director->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
	}
	// if the frame's height is smaller than the height of medium resource size, select small resource.
	else
	{
		searchPath.push_back(smallResource.directory);

		director->setContentScaleFactor(smallResource.size.width/designResolutionSize.width);
	}

	// set searching path
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
