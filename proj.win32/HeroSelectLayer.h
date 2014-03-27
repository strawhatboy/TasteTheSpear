#pragma once

#include "cocos2d.h"
#include "myLib.h"
#include "GameObjectTypesLoader.h"
#include "GameDirector.h"
#include "ScrollLayer.h"
#include "UserDefaultUtils.h"
#include "GameScene.h"

USING_NS_CC;

class HeroSelectLayer :
	public CCLayer
{
private:
	void heroSelected(CCObject* obj);
	vector<string>* m_HerosIDs;

	CCLayer* getChildLayer(HeroType* heroType);

public:
	virtual bool init();
	virtual void onEnter();
	HeroSelectLayer(void);
	~HeroSelectLayer(void);

	CREATE_FUNC(HeroSelectLayer);
};

