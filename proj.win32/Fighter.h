#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Fighter :
	public cocos2d::CCSprite
{
public:
	virtual bool init(void);
	Fighter(void);
	~Fighter(void);
	CREATE_FUNC(Fighter);
};

