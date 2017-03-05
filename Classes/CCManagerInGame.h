#pragma once
#include "Guzzler.h"
#include "Singleton.h"


class CCManagerInGame: public Singleton<CCManagerInGame>
{
public:
	CCManagerInGame(void);
	virtual ~CCManagerInGame(void);
	
	int scoreGame;
	Guzzler* guzzlerInGame;
};

