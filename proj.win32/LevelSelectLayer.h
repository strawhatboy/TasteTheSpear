#pragma once

#include "cocos2d.h"
#include "GameObjectTypesLoader.h"
#include "ScrollLayer.h"
#include "GameDirector.h"
#include "HeroSelectScene.h"

USING_NS_CC;

class LevelSelectLayer :
	public CCLayer
{
private:
	void levelSelected(CCObject* obj);
	vector<string>* m_LevelsIDs;

public:
	virtual bool init(const char* districtTypeID = "");

	LevelSelectLayer(void);
	~LevelSelectLayer(void);

	static LevelSelectLayer* create(const char* districtTypeID = "")
	{
		auto p = new LevelSelectLayer();
		if (p && p->init(districtTypeID))
		{
			p->autorelease();
			return p;
		}
		else
		{
			CC_SAFE_DELETE(p);
			return NULL;
		}
	}
};

