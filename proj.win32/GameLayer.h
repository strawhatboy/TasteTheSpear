#pragma once

#include "cocos2d.h"
#include "myLib.h"
#include "GameEventsMacros.h"
#include "GameHudLayer.h"

USING_NS_CC;

#define TAG_GAMELAYER 250

class GameLayer :
	public CCLayer
{
	CCDictionary* m_Touches;

public:
	virtual bool init(void);

	virtual void registerWithTouchDispatcher();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	GameLayer(void);
	~GameLayer(void);

	CREATE_FUNC(GameLayer);
};

