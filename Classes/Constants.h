#pragma once

#define kDesignResolutionWidth 1024
#define kDesignResolutionHeight 768

#define kZindexTree 15
#define kZIndexCloud 10
#define kZIndexWall 20
#define kZIndexEnemy 90
#define kZHealthBar 95
#define kZGuzzler 100

#define kSpeedScrollCloud 100
#define kSpeedScrollTree 50

#define kTypeEnemy1 1
#define kTypeEnemy2 2
#define kTypeEnemy3 3
#define kTypeEnemy4 4
#define kTypeEnemy5 5

#define sttGuzzlerNormal 1
#define sttGuzzlerOpenningDontEat 2
#define sttGuzzlerOpenningEat 3
#define sttGuzzlerEating 4
#define sttGuzzlerClosingDontEat 5
#define sttGuzzlerClosingEat 6
#define sttGuzzlerOpenDontEat 7
#define sttGuzzlerDeath 8

#define GETWINSIZE_WIDTH (Director::getInstance()->getWinSize().width)
#define GETWINSIZE_HEIGHT (Director::getInstance()->getWinSize().height)

#define GETVISIBLESIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define GETVISIBLESIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)

#define kStartPosEnemy 1024
#define kDistanceMin 100
#define kDistanceMax 200
#define kSpeedEnemy 100

#define kSttEnemyNormal 1
#define kSttEnemyCollide 2