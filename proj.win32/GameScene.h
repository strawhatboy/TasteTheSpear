#pragma once
#include "cocos2d.h"
#include "myLib.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene :
	public CCScene
{
public:
	virtual bool init();

	GameScene(void);
	~GameScene(void);

	CREATE_FUNC(GameScene);
};

